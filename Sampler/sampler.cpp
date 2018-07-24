#include "sampler.h"

Sampler::Sampler():count(0),numSamples(1),numSets(1),jump(0)
{

}

Sampler::Sampler(const int &_numSamples):numSamples(_numSamples),count(0),numSets(1),jump(0)
{

}

int Sampler::getNumSamples() const
{
    return numSamples;
}

Point2D Sampler::sampleUnitSquare(){
    return (samples[count++%(numSamples*numSets)]);
}
