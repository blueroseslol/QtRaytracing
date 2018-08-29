#include "pointlight.h"
#include "World.h"
PointLight::PointLight():Light(),ls(1.0),color(1.0),location(0)
{

}

PointLight::PointLight(const PointLight &pointLight):Light(pointLight),
    ls(pointLight.ls),color(pointLight.color),location(pointLight.location)
{

}

PointLight::PointLight( PointLight&& pointLight):Light(pointLight),
    ls(pointLight.ls),color(pointLight.color),location(pointLight.location)
{

}

Vector3D PointLight::getDirection(ShadeRec &sr)
{
    return (location-sr.hit_point).hat();
}

RGBColor PointLight::L(ShadeRec &sr)
{
    return ls*color;
}

bool PointLight::inShadow(const Ray &ray, const ShadeRec &sr) const
{
    float t;
    float d=location.distance(ray.origin);

    for(int j=0;j<sr.w.scene.length();j++){
        if(sr.w.scene[j]->shadowHit(ray,t)&&t<d)
            return true;
    }
    return false;
}
