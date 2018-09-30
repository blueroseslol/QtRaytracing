#ifndef __TRIANGLE__
#define __TRIANGLE__
#include "Geometry/Geometry.h"

class Triangle: public Geometry {
public:
    Triangle();

    Triangle(const Point3D& a, const Point3D& b, const Point3D& c);

    Triangle(const Triangle& triangle);

    Triangle(Triangle&& triangle);

    ~Triangle();

    Triangle&	operator= (const Triangle& rhs);

    virtual BBox getBoundingBox() override;

    void computeNormal();

    virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;

    virtual bool shadowHit(const Ray& ray, double& tmin) const override;
private:
    Point3D	v0, v1, v2;
    Normal	normal;
};
#endif

