#ifndef PATHTRACE_H
#define PATHTRACE_H


#include "Tracer/Tracer.h"

class PathTrace: public Tracer {
    public:

    PathTrace();

    PathTrace(World* _worldPtr);

    virtual RGBColor trace_ray(const Ray& ray, const int depth) const override;

    virtual RGBColor trace_ray(const Ray& ray, double& tmin, const int depth) const;
};

#endif // PATHTRACE_H
