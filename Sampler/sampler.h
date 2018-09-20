#ifndef SAMPLER_H
#define SAMPLER_H
#include "Utilities/Point2D.h"
#include "Utilities/Point3D.h"
#include <QVector>
class Sampler
{
public:
    Sampler();

    Sampler(const int& _numSamples);

    Sampler(const int& _numSamples,const int& _numSets);

    virtual void generateSampler();

    void setupShuffledIndices();

    void shuffleSamples();

    int getNumSamples() const;

    virtual Point2D sampleUnitSquare();
    void map_samples_to_unit_disk();
    void map_samples_to_hemisphere(const float exp);
    void map_samples_to_sphere();
    Point3D sampleHemisphere();
protected:
    int numSamples;
    int numSets;
    QVector<Point2D> samples;
    QVector<int> shuffledIndices;
    QVector<Point2D>	 diskSamples;
    QVector<Point3D> hemisphereSamples;		// sample points on a unit hemisphere
    QVector<Point3D> sphereSamples;
    unsigned long count;
    int jump;
};

#endif // SAMPLER_H
