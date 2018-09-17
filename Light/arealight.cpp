#include "arealight.h"
#include "World.h"
#include "Geometry/Geometry.h"
#include "Material/material.h"
AreaLight::AreaLight():Light()
{

}

AreaLight::AreaLight(const AreaLight &al):Light(al)
{

}

AreaLight::AreaLight(AreaLight &&al):Light(al)
{

}

void AreaLight::setObject(Geometry *objectPtr)
{
    object_ptr=objectPtr;
}

Vector3D AreaLight::getDirection(ShadeRec &sr)
{
    samplerPoint=object_ptr->sampler();
    lightNormal=object_ptr->getNormal(samplerPoint);
    wi=samplerPoint-sr.hit_point;
    wi.normalize();
    return wi;
}

RGBColor AreaLight::L(ShadeRec &sr)
{
    float ndotd=-lightNormal*wi;
	if (ndotd > 0)
		return object_ptr->getMaterial()->getLe(sr);
    else
        return RGBColor();
}

bool AreaLight::inShadow(const Ray &ray, const ShadeRec &sr) const
{
    float t;
    float ts=(samplerPoint-ray.origin)*ray.direction;

    for(int j=0;j<sr.w.scene.length();j++){
        if(sr.w.scene[j]->shadowHit(ray,t)&&t<ts)
            return true;
    }
    return false;
}

float AreaLight::G(const ShadeRec &sr) const
{
    float ndotd=-lightNormal*wi;
    float d2=samplerPoint.d_squared(sr.hit_point);

    return ndotd/d2;
}

float AreaLight::pdf(const ShadeRec &sr) const
{
    return object_ptr->pdf(sr);
}
