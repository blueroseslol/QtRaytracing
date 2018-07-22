#ifndef JITTERED_H
#define JITTERED_H
#include "Sampler/sampler.h"

class Jittered : public Sampler
{
public:
    Jittered();
private:
    virtual void generateSampler();
};

#endif // JITTERED_H
