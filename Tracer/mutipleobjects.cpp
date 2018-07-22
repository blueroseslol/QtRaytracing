#include "mutipleobjects.h"
#include "World.h"
MutipleObjects::MutipleObjects()
{

}

MutipleObjects::MutipleObjects(World *w_ptr):Tracer(w_ptr){
//    world_ptr=w_ptr;
}

RGBColor MutipleObjects::trace_ray(const Ray &ray) const
{
    ShadeRec sr(world_ptr->hit_bare_bones_objects(ray));

    if(sr.hit_an_object)
        return sr.color;
    else
        return world_ptr->setting->backergroundColor;
}
