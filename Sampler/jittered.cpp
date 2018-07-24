#include "jittered.h"
#include "Utilities/Constants.h"
Jittered::Jittered()
{

}

Jittered::Jittered(const int &_numSamples):Sampler(_numSamples)
{
    generateSampler();
}

Jittered::Jittered(const int &_numSamples, const int &_numSets):Sampler(_numSamples,_numSets)
{
    generateSampler();
}

void Jittered::generateSampler()
{
    int n=(int)sqrt(numSamples);
    for(int p=0;p<numSets;p++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                samples.push_back(Point2D((k+rand_float())/n,(j+rand_float())/n));
            }
        }
    }
}
