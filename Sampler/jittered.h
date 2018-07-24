#ifndef JITTERED_H
#define JITTERED_H
#include "Sampler/sampler.h"

class Jittered : public Sampler
{
public:
    Jittered();

    Jittered(const int& _numSamples);

    Jittered(const int& _numSamples,const int& _numSets);
private:
    virtual void generateSampler();
};

#endif // JITTERED_H
