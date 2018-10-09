#include "sphericalmap.h"
#include "Utilities/Constants.h"
SphericalMap::SphericalMap()
{}

void SphericalMap::getTexelCoordinates(const Point3D &hit_point, const int xres, const int yres, int &row, int &column) const
{
    float theta=acos(hit_point.y);
    float phi=atan2(hit_point.x,hit_point.z);
    if(phi<0.0)
        phi+=TWO_PI;

    float u=phi*invTWO_PI;
    float v=1-theta*invPI;

    column=(int)((xres-1)*u);
    row=(int)((yres-1)*v);
}
