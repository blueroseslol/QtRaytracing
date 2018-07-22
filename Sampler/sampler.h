#ifndef SAMPLER_H
#define SAMPLER_H
#include "Utilities/Point2D.h"
#include <QVector>
class Sampler
{
public:
    Sampler();

    virtual void generateSampler()=0;

    void setupShuffledIndices();

    void shuffleSamples();

    int getNumSamples() const;

    Point2D sampleUnitSquare();
protected:
    int numSamples;
    int numSets;
    QVector<Point2D> samples;
    QVector<int> shuffledIndices;
    unsigned long count;
    int jump;
};

#endif // SAMPLER_H
