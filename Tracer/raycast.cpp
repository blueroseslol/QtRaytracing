#include "raycast.h"
#include <QDebug>
RayCast::RayCast()
{

}

RayCast::RayCast(World *w_ptr):Tracer(w_ptr)
{

}

RGBColor RayCast::trace_ray(const Ray &ray, const int depth) const
{
        ShadeRec sr(world_ptr->hitObject(ray));
        if (sr.hit_an_object) {
            sr.ray = ray;			// used for specular shading
            return sr.material_ptr->shade(sr);
        }
        else
            return world_ptr->setting->backergroundColor;
}
