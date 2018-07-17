#ifndef TRACER_H
#define TRACER_H
#include "Utilities/RGBColor.h"
#include "world.h"

class Tracer
{
public:
    Tracer();

    Tracer(World *w_ptr);

    virtual RGBColor trace_ray(const Ray& ray) const;
protected:
    World *world_ptr;
};

#endif // TRACER_H
