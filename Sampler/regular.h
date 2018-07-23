﻿#ifndef REGULAR_H
#define REGULAR_H
#include "Sampler/sampler.h"

class Regular : public Sampler
{
public:
    Regular();

    Regular(const int& _numSamples);
private:
    virtual void generateSampler();
};

#endif // REGULAR_H
