#include "jittered.h"

Jittered::Jittered()
{

}

void Jittered::generateSampler()
{
    int n=(int)sqrt(numSamples);
    for(int p=0;p<numSets;p++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                Point2D sp((k+rand_float())/n,(j+rand_float())/n);
                samples.push_back(sp);
            }
        }
    }
}
