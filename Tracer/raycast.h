#ifndef RAYCAST_H
#define RAYCAST_H
#include "Tracer/tracer.h"

class RayCast : public Tracer
{
public:
    RayCast();

    RayCast(World *w_ptr);

    virtual RGBColor trace_ray(const Ray& ray,const int depth) const override;
};

#endif // RAYCAST_H
