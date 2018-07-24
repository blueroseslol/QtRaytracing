#include "regular.h"
#include <QDebug>
Regular::Regular()
{

}

Regular::Regular(const int &_numSamples):Sampler(_numSamples)
{

}

Point2D Regular::sampleUnitSquare()
{
    return samples[count++%numSamples];
}

void Regular::generateSampler()
{
    int n=(int)sqrt(numSamples);
    for(int j=0;j<n;j++){
        for(int k=0;k<n;k++){
            samples.push_back(Point2D((float)k/n,(float)j/n));
        }
    }
}
