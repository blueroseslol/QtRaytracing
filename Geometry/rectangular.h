#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Geometry/Geometry.h"

class Sampler;
class Rectangular : public Geometry
{
public:
    Rectangular();

    Rectangular(const Rectangular& rect);

    Rectangular(Rectangular&& rect);

    Rectangular(const Point3D &_p0, const Vector3D &_a, const Vector3D &_b, const Normal &_normal);

    virtual bool hit(const Ray &ray, double &tmin, ShadeRec &sr) const;

    virtual bool shadowHit(const Ray &ray, double &tmin) const;

    void setSampler(Sampler *sampler);

    virtual Point3D sampler();

    virtual float pdf(ShadeRec& sr);

    virtual Normal getNormal(const Point3D& p) const override;

    Rectangular(const Point3D &_p0, const Vector3D &_a, const Vector3D &_b);

    virtual BBox getBoundingBox();
private:
    Point3D p0;
    Vector3D a;
    Vector3D b;
    double			a_len_squared;	// square of the length of side a
    double			b_len_squared;	// square of the length of side b
    Normal normal;
    Sampler *sampler_ptr;
    float			area;
    float inv_area;

    static const double kEpsilon;
};

#endif // RECTANGLE_H
