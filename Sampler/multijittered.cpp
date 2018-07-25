#include "multijittered.h"
#include "Utilities/Constants.h"
MultiJittered::MultiJittered()
{

}

MultiJittered::MultiJittered(const int _numSamples):Sampler(_numSamples)
{
    generateSampler();
}

MultiJittered::MultiJittered(const int _numSamples, const int _numSets):Sampler(_numSamples,_numSets)
{
    generateSampler();
}

void MultiJittered::generateSampler()
{
    // numSamples needs to be a perfect square

    int n = sqrt(numSamples);
    float subcell_width = 1.0 / ((float) numSamples);

    // fill the samples array with dummy points to allow us to use the [ ] notation when we set the
    // initial patterns

    samples=QVector<Point2D>(numSamples * numSets,Point2D());
    // distribute points in the initial patterns

    for (int p = 0; p < numSets; p++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                samples[i * n + j + p * numSamples].x = (i * n + j) * subcell_width + rand_float(0, subcell_width);
                samples[i * n + j + p * numSamples].y = (j * n + i) * subcell_width + rand_float(0, subcell_width);
            }

    // shuffle x coordinates

    for (int p = 0; p < numSets; p++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                int k = rand_int(j, n - 1);
                float t = samples[i * n + j + p * numSamples].x;
                samples[i * n + j + p * numSamples].x = samples[i * n + k + p * numSamples].x;
                samples[i * n + k + p * numSamples].x = t;
            }

    // shuffle y coordinates

    for (int p = 0; p < numSets; p++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                int k = rand_int(j, n - 1);
                float t = samples[j * n + i + p * numSamples].y;
                samples[j * n + i + p * numSamples].y = samples[k * n + i + p * numSamples].y;
                samples[k * n + i + p * numSamples].y = t;
        }
}
