#ifndef SAMPLER_H
#define SAMPLER_H
#include "Utilities/Point2D.h"
#include <QVector>
class Sampler
{
public:
    Sampler();

    Sampler(const int& _numSamples);

    Sampler(const int& _numSamples,const int& _numSets);

    virtual void generateSampler()=0;

    void setupShuffledIndices();

    void shuffleSamples();

    int getNumSamples() const;

    virtual Point2D sampleUnitSquare();
protected:
    int numSamples;
    int numSets;
    QVector<Point2D> samples;
    QVector<int> shuffledIndices;
    unsigned long count;
    int jump;
};

#endif // SAMPLER_H
