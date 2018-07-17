#ifndef SINGLESPHERE_H
#define SINGLESPHERE_H
#include "tracer.h"

class SingleSphere : public Tracer
{
public:
    SingleSphere(World *w_ptr);

    RGBColor trace_ray(const Ray &ray) const;
};

#endif // SINGLESPHERE_H
