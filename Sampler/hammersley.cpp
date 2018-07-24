#include "hammersley.h"

Hammersley::Hammersley()
{

}

Hammersley::Hammersley(const int& _numSamples):Sampler(_numSamples)
{
    generateSampler();
}

Hammersley::Hammersley(const int& _numSamples, const int& _numSets):Sampler(_numSamples,_numSets)
{
    generateSampler();
}

double Hammersley::phi(int j) {
    double x = 0.0;
    double f = 0.5;

    while (j) {
        x += f * (double) (j % 2);
        j /= 2;
        f *= 0.5;
    }
    return x;
}

void Hammersley::generateSampler()
{
    for (int p = 0; p < numSets; p++){
            for (int j = 0; j < numSamples; j++) {
                samples.push_back(Point2D((float) j / (float) numSamples, phi(j)));
            }
    }
}

