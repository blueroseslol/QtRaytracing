#include "environmentlight.h"

EnvironmentLight::EnvironmentLight():Light()
{

}

EnvironmentLight::EnvironmentLight(const EnvironmentLight &el):Light(el)
{

}

EnvironmentLight::EnvironmentLight(EnvironmentLight &&el):Light(el)
{

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
    float ts=(samplerPoint-ray.origin)*ray.direction;

    for(int j=0;j<sr.w.scene.length();j++){
        if(sr.w.scene[j]->shadowHit(ray,t)&&t<ts)
            return true;
    }
    return false;
}

float EnvironmentLight::pdf(const ShadeRec &sr) const
{
    return 0;
}
