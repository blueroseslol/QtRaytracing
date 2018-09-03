#include "arealighting.h"

AreaLighting::AreaLighting()
{

}

RGBColor AreaLighting::trace_ray(const Ray &ray, const int depth) const
{
    ShadeRec sr(world_ptr->hitObject(ray));

    if(sr.hit_an_object){
        sr.ray=ray;
        return sr.material_ptr->areaLightShade(sr);
    }else
        return world_ptr->setting->backergroundColor;
}
