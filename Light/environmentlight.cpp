#include "environmentlight.h"
#include "Material/material.h"
#include "Utilities/Constants.h"
EnvironmentLight::EnvironmentLight():Light(),sampler_ptr(nullptr),material_ptr(nullptr)
{

}

//EnvironmentLight::EnvironmentLight(const EnvironmentLight &el):Light(el)
//{

//}

//EnvironmentLight::EnvironmentLight(EnvironmentLight &&el):Light(el)
//{

//}

void EnvironmentLight::setSampler(Sampler *_sampler_ptr)
{
    sampler_ptr=_sampler_ptr;
}

void EnvironmentLight::setMaterial(Material *_material_ptr)
{
    material_ptr=_material_ptr;
}

Vector3D EnvironmentLight::getDirection(ShadeRec &sr)
{
    w=sr.normal;
    v=Vector3D(0.0034,1,0.0071)^w;
    v.normalize();
    u=v^w;
    Point3D sp=sampler_ptr->sampleHemisphere();
    wi=sp.x*u+sp.y*v+sp.z*w;
    return wi;
}

RGBColor EnvironmentLight::L(ShadeRec &sr)
{
    return material_ptr->getLe(sr);
}

bool EnvironmentLight::inShadow(const Ray &ray, const ShadeRec &sr) const
{
    float t;
    for(int j=0;j<sr.w.scene.length();j++){
        if(sr.w.scene[j]->shadowHit(ray,t))
            return true;
    }
    return false;
}

float EnvironmentLight::pdf(const ShadeRec &sr) const
{
   return sr.normal * wi * invPI;
}
