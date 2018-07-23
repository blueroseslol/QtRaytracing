#include "sampler.h"

Sampler::Sampler()
{

}

int Sampler::getNumSamples() const
{
    return numSamples;
}

Point2D Sampler::sampleUnitSquare(){
    return (samples[count++%(numSamples*numSets)]);
}
