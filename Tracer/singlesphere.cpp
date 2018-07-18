#include "singlesphere.h"
#include "Utilities/ShadeRec.h"
#include "World.h"
SingleSphere::SingleSphere(World *w_ptr){
    world_ptr=w_ptr;
}

RGBColor SingleSphere::trace_ray(const Ray &ray) const{
    ShadeRec sr(*world_ptr);
    double t;
    if(world_ptr->sphere.hit(ray,t,sr))
        return RGBColor(1.0,0.0,0.0);
    else
        return RGBColor();
}
