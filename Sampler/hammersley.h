#ifndef HAMMERSLEY_H
#define HAMMERSLEY_H
#include "Sampler/sampler.h"

class Hammersley : public Sampler
{
public:
    Hammersley();
    Hammersley(const int& _numSamples, const int& _numSets);
    Hammersley(const int& _numSamples);
    void generateSampler();
private:
    double phi(int j);
};

#endif // HAMMERSLEY_H
