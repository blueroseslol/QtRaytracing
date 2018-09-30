#ifndef BOX_H
#define BOX_H
#include "Geometry/Geometry.h"

class Box : public Geometry
{
public:
    Box();

    Box(const double x0, const double x1,
        const double y0, const double y1,
        const double z0, const double z1);

    Box(const Point3D p0, const Point3D p1);

    Box(const Box& box);

    Box(Box&& box);

    Box& operator= (const Box& rhs);

    ~Box();

    virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

    Normal get_normal(const int face_hit) const;

    virtual bool shadowHit(const Ray& ray, double& tmin) const;

    virtual BBox getBoundingBox();

private:

    double x0, x1, y0, y1, z0, z1;

    static const double kEpsilon;
};

#endif // BOX_H
