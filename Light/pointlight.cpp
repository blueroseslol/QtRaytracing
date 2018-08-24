#include "pointlight.h"

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
