#include "singlesphere.h"
#include "Utilities/ShadeRec.h"
#include "World.h"
SingleSphere::SingleSphere(World *w_ptr){
    world_ptr=w_ptr;
    sphere=new Sphere(Point3D(0.0,0.0,-1),0.5);
    sphere->setColor(RGBColor(1.0,0,0));
}

RGBColor SingleSphere::trace_ray(const Ray &ray) const{
    ShadeRec sr(*world_ptr);
    double t;
    if(sphere->hit(ray,t,sr))
        return RGBColor(1.0,0.0,0.0);
    else{
        Vector3D unit_direction = ray.direction;
        unit_direction.normalize();
        float t = 0.5*(unit_direction.y + 1.0);
        return (1.0 - t)*RGBColor(1.0, 1.0, 1.0) + t*RGBColor(0.5, 0.7, 1.0);
    }
}
