#include "emissive.h"

Emissive::Emissive()
{

}

RGBColor Emissive::areaLightShade(ShadeRec &sr)
{
    if(-sr.normal*sr.ray.direction>0.0)
        return ls*ce;
    else
        return RGBColor(0);
}
