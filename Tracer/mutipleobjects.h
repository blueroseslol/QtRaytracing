#ifndef MUTIPLEOBJECTS_H
#define MUTIPLEOBJECTS_H
#include "Tracer/tracer.h"

class MutipleObjects : public Tracer
{
public:
    MutipleObjects();
    MutipleObjects(World *w_ptr);
    RGBColor trace_ray(const Ray &ray) const;
};

#endif // MUTIPLEOBJECTS_H
