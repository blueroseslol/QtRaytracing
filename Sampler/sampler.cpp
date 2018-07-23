#include "sampler.h"

Sampler::Sampler()
{

}

Sampler::Sampler(const int &_numSamples):numSamples(_numSamples)
{

}

int Sampler::getNumSamples() const
{
    return numSamples;
}

Point2D Sampler::sampleUnitSquare(){
    return (samples[count++%(numSamples*numSets)]);
}
