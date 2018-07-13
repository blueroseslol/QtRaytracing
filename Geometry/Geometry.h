﻿#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "Utilities/ShadeRec.h"
#include "Utilities/Ray.h"
#include "Utilities/RGBColor.h"

class Geometry
{
public:
    Geometry();
    virtual bool hit(const Ray& ray,double& tmin,ShadeRec& sr) const =0;
protected:
    RGBColor color;
};

#endif
