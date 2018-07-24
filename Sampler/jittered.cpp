#include "jittered.h"
#include "Utilities/Constants.h"
#include <QDebug>
Jittered::Jittered()
{

}

Jittered::Jittered(const int &_numSamples):Sampler(_numSamples)
{

}

void Jittered::generateSampler()
{
    int n=(int)sqrt(numSamples);
    for(int p=0;p<numSets;p++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                Point2D sp((k+float_rand())/n,(j+float_rand())/n);
                samples.push_back(sp);
            }
        }
    }
}
