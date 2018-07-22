﻿#ifndef TRACER_H
#define TRACER_H
#include "Utilities/RGBColor.h"
#include "Utilities/Ray.h"
#include "Utilities/ShadeRec.h"
class World;

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
