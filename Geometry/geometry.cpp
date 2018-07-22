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
