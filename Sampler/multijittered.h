#ifndef MULTIJITTERED_H
#define MULTIJITTERED_H
#include "Sampler/sampler.h"

class MultiJittered : public Sampler
{
public:
    MultiJittered();

    MultiJittered(const int _numSamples);

    MultiJittered(const int _numSamples, const int _numSets);
private:
    virtual void generateSampler() override;
};

#endif // MULTIJITTERED_H
