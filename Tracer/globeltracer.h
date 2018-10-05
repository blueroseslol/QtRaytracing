#ifndef GLOBELTRACER_H
#define GLOBELTRACER_H
#include "Tracer/tracer.h"

class GlobelTracer : public Tracer
{
public:
    GlobelTracer();

    GlobelTracer(World* _worldPtr);

    ~GlobelTracer();

    virtual RGBColor trace_ray(const Ray& ray, const int depth) const override;
};

#endif // GLOBELTRACER_H
