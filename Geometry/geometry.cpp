#include "Geometry/Geometry.h"

Geometry::Geometry():color(RGBColor()){}

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
