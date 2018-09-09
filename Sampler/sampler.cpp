#include "sampler.h"
//#include <QDebug>
#include <algorithm>
#include "Utilities/Constants.h"

Sampler::Sampler():count(0),numSamples(1),numSets(1),jump(0)
{
    setupShuffledIndices();
}

Sampler::Sampler(const int &_numSamples):numSamples(_numSamples),count(0),numSets(1),jump(0)
{
    setupShuffledIndices();
}

Sampler::Sampler(const int &_numSamples,const int& _numSets):numSamples(_numSamples),count(0),numSets(_numSets),jump(0)
{
    setupShuffledIndices();
}

//将几个sets的采样点进行打乱处理
//个人感觉没必要，因为c++11的那个随机数是均匀的
void Sampler::setupShuffledIndices()
{
    shuffledIndices.reserve(numSamples*numSets);
    QVector<int> indices;
    for(int j=0;j<numSamples;j++){
        indices.push_back(j);
    }
    for(int p=0;p<numSets;p++){
        std::random_shuffle(indices.begin(),indices.end());
        for(int j=0;j<numSamples;j++){
            shuffledIndices.push_back(indices[j]);
        }
    }
}

int Sampler::getNumSamples() const
{
    return numSamples;
}

Point2D Sampler::sampleUnitSquare(){
    if(count%numSamples==0){
        //TODO:qrand()是个伪随机函数，先测试效果，如果不行再换
        jump=(qrand()%numSets)*numSamples;
    }
    return samples[jump+count++%(numSamples)];
//    return (samples[count++%(numSamples*numSets)]);

//setupShuffledIndices版本的sampleUnitSquare
    /*
    if(count%numSamples==0)
        jump=(rand_int(0,32767)%numSets)*numSamples;
    return samples[jump+shuffledIndices[jump+count++%numSamples]];
    */
}

void Sampler::map_samples_to_unit_disk(void) {
    int size = samples.size();
    float r, phi;		// polar coordinates
    Point2D sp; 		// sample point on unit disk

    diskSamples.reserve(size);

    for (int j = 0; j < size; j++) {
         // map sample point to [-1, 1] X [-1,1]

        sp.x = 2.0 * samples[j].x - 1.0;
        sp.y = 2.0 * samples[j].y - 1.0;

        if (sp.x > -sp.y) {			// sectors 1 and 2
            if (sp.x > sp.y) {		// sector 1
                r = sp.x;
                phi = sp.y / sp.x;
            }
            else {					// sector 2
                r = sp.y;
                phi = 2 - sp.x / sp.y;
            }
        }
        else {						// sectors 3 and 4
            if (sp.x < sp.y) {		// sector 3
                r = -sp.x;
                phi = 4 + sp.y / sp.x;
            }
            else {					// sector 4
                r = -sp.y;
                if (sp.y != 0.0)	// avoid division by zero at origin
                    phi = 6 - sp.x / sp.y;
                else
                    phi  = 0.0;
            }
        }

        phi *= PI / 4.0;

        diskSamples[j].x = r * cos(phi);
        diskSamples[j].y = r * sin(phi);
    }

    samples.erase(samples.begin(), samples.end());
}


// ------------------------------------------------------------------- map_samples_to_hemisphere

// Maps the 2D sample points to 3D points on a unit hemisphere with a cosine power
// density distribution in the polar angle

void Sampler::map_samples_to_hemisphere(const float exp) {
    int size = samples.size();
    hemisphereSamples.reserve(numSamples * numSets);

    for (int j = 0; j < size; j++) {
        float cos_phi = cos(2.0 * PI * samples[j].x);
        float sin_phi = sin(2.0 * PI * samples[j].x);
        float cos_theta = pow((1.0 - samples[j].y), 1.0 / (exp + 1.0));
        float sin_theta = sqrt (1.0 - cos_theta * cos_theta);
        float pu = sin_theta * cos_phi;
        float pv = sin_theta * sin_phi;
        float pw = cos_theta;
        hemisphereSamples.push_back(Point3D(pu, pv, pw));
    }
}


// ------------------------------------------------------------------- map_samples_to_sphere

// Maps the 2D sample points to 3D points on a unit sphere with a uniform density
// distribution over the surface
// this is used for modelling a spherical light

void Sampler::map_samples_to_sphere(void) {
    float r1, r2;
    float x, y, z;
    float r, phi;

    sphereSamples.reserve(numSamples * numSets);

    for (int j = 0; j < numSamples * numSets; j++) {
        r1 	= samples[j].x;
        r2 	= samples[j].y;
        z 	= 1.0 - 2.0 * r1;
        r 	= sqrt(1.0 - z * z);
        phi = TWO_PI * r2;
        x 	= r * cos(phi);
        y 	= r * sin(phi);
        sphereSamples.push_back(Point3D(x, y, z));
    }
}

Point3D Sampler::sampleHemisphere() {
    if (count % numSamples == 0)  									// start of a new pixel
        jump = (qrand() % numSets) * numSamples;

    return (hemisphereSamples[jump + shuffledIndices[jump + count++ % numSamples]]);
}
