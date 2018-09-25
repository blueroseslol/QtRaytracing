#include "emissive.h"

Emissive::Emissive()
{

}

void Emissive::scaleRadiance(const float _ls)
{
    ls=_ls;
}

void Emissive::setCe(const float &r, const float &g, const float &b)
{
    ce=RGBColor(r,g,b);
}

RGBColor Emissive::getLe(ShadeRec &sr) const
{
    return ls * ce;
}

RGBColor Emissive::shade(ShadeRec &sr)
{
    if (-sr.normal * sr.ray.direction > 0.0)
        return ls * ce;
    else
        return RGBColor();
}

RGBColor Emissive::areaLightShade(ShadeRec &sr)
{
    if(-sr.normal*sr.ray.direction>0.0)
        return ls*ce;
    else
        return RGBColor();
}
