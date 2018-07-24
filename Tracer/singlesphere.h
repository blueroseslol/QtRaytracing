#ifndef SINGLESPHERE_H
#define SINGLESPHERE_H
#include "tracer.h"
#include "Geometry/sphere.h"

class SingleSphere : public Tracer
{
public:
    SingleSphere(World *w_ptr);

    RGBColor trace_ray(const Ray &ray) const;
private:
    Sphere *sphere;
};

#endif // SINGLESPHERE_H
