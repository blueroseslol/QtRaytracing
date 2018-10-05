#include "globeltracer.h"

GlobelTracer::GlobelTracer()
{

}

GlobelTracer::GlobelTracer(World *_worldPtr):Tracer(_worldPtr)
{

}

GlobelTracer::~GlobelTracer()
{

}

RGBColor GlobelTracer::trace_ray(const Ray &ray, const int depth) const
{
    if (depth > world_ptr->setting->maxDepth)
        return RGBColor();
    else {
        ShadeRec sr(world_ptr->hitObject(ray));
        if (sr.hit_an_object) {
            sr.depth = depth;
            sr.ray = ray;

            return sr.material_ptr->globalShade(sr);
        }
        else
            return world_ptr->setting->backergroundColor;
    }
}
