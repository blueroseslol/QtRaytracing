#ifndef SPHERICALMAP_H
#define SPHERICALMAP_H
#include "Mapping.h"

class SphericalMap : public Mapping
{
public:
    SphericalMap();

    virtual void getTexelCoordinates(const Point3D &hit_point, const int xres, const int yres, int &row, int &column) const override;
};

#endif // SPHERICALMAP_H
