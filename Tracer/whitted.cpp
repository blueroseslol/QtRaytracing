#include "Tracer/Whitted.h"
#include "World.h"
#include "Utilities/ShadeRec.h"
#include "Material/Material.h"
#include "Utilities/Constants.h"
#include <QDebug>
Whitted::Whitted():Tracer()
{}

Whitted::Whitted(World* _worldPtr):Tracer(_worldPtr)
{}

Whitted::~Whitted() {}

RGBColor Whitted::trace_ray(const Ray& ray, const int depth) const {
    if (depth > world_ptr->setting->maxDepth)
        return RGBColor();
    else {
        ShadeRec sr(world_ptr->hitObject(ray));
		if (sr.hit_an_object) {
			sr.depth = depth;
			sr.ray = ray;	

            return sr.material_ptr->shade(sr);
		}
		else
            return world_ptr->setting->backergroundColor;
    }
}

RGBColor Whitted::trace_ray(const Ray &ray, double &tmin, const int depth) const
{
    if(depth>world_ptr->setting->maxDepth){
        return RGBColor();
    }else{
        ShadeRec sr(world_ptr->hitObject(ray));
        if(sr.hit_an_object){
            sr.depth=depth;
            sr.ray=ray;
            tmin=sr.t;
            return sr.material_ptr->shade(sr);
        }else{
            tmin=kHugeValue;
            return world_ptr->setting->backergroundColor;
        }
    }
}
