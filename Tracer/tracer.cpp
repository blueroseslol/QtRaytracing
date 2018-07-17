#include "tracer.h"
#include "World.h"

Tracer::Tracer():world_ptr(nullptr)
{

}

Tracer::Tracer(World *w_ptr):world_ptr(w_ptr){

}

void Tracer::trace_ray(const Ray &ray) const{
    return RGBColor();
}
