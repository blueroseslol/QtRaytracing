#ifndef PLANE_H
#define PLANE_H
#include "Geometry/Geometry.h"

class Plane : public Geometry
{
public:
    Plane();

    Plane(const Point3D& point, const Normal& normal);

    Plane(const Plane& plane);

    Plane(Plane&& plane);

    Plane& operator= (const Plane& rhs);
    Plane& operator= (Plane&& rhs);

    virtual ~Plane();

    virtual bool
    hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

    virtual bool shadowHit(const Ray &ray, double &tmin) const;

private:
    Point3D 	a;   				// point through which plane passes
    Normal 	n;					// normal to the plane

    static const double kEpsilon;   // for shadows and secondary rays
};

#endif // PLANE_H
