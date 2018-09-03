#ifndef AREALIGHTING_H
#define AREALIGHTING_H
#include "Tracer/tracer.h"

class AreaLighting : public Tracer
{
public:
    AreaLighting();

    virtual RGBColor trace_ray(const Ray &ray, const int depth) const;
};

#endif // AREALIGHTING_H
