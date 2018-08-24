#include "Geometry/Geometry.h"
#include <QDebug>
#include "Material/material.h"
Geometry::Geometry():color(RGBColor()),material_ptr(nullptr){}

Geometry::~Geometry(){}

RGBColor Geometry::getColor() const
{
    return color;
}

void Geometry::setColor(const RGBColor& _color)
{
    color=_color;
}

void Geometry::setMaterial(Material *mPtr)
{
    material_ptr=mPtr;
}

Material *Geometry::getMaterial() const
{
    return material_ptr;
}
