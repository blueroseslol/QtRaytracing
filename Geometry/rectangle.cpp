#include "rectangle.h"
#include "Sampler/sampler.h"
const double Rectangle::kEpsilon = 0.001;
Rectangle::Rectangle():Geometry()
{

}

Rectangle::Rectangle(Point3D _p0, Vector3D _a, Vector3D _b, Normal _normal):Geometry(),p0(_p0),a(_a),b(_b),normal(_normal)
{

}

bool Rectangle::hit(const Ray &ray, double &tmin, ShadeRec &sr) const
{
    double t = (p0 - ray.origin) * normal / (ray.direction * normal);

    if (t <= kEpsilon)
        return (false);

    Point3D p = ray.origin + t * ray.direction;
    Vector3D d = p - p0;

    double ddota = d * a;

    if (ddota < 0.0 || ddota > a_len_squared)
        return (false);

    double ddotb = d * b;

    if (ddotb < 0.0 || ddotb > b_len_squared)
        return (false);

    tmin 				= t;
    sr.normal 			= normal;
    sr.local_hit_point 	= p;

    return (true);
}

bool Rectangle::shadowHit(const Ray &ray, float &tMin) const
{
    double t = (p0 - ray.origin) * normal / (ray.direction * normal);

    if (t <= kEpsilon)
        return false;

    Point3D p = ray.origin + t * ray.direction;
    Vector3D d = p - p0;

    double ddota = d * a;

    if (ddota < 0.0 || ddota > a_len_squared)
        return (false);

    double ddotb = d * b;

    if (ddotb < 0.0 || ddotb > b_len_squared)
        return (false);

    tMin 				= t;

    return true;
}

Point3D Rectangle::sampler()
{
    Point2D sample_point=sampler_ptr->sampleUnitSquare();
    return p0+sample_point.x*a+sample_point.y*b;
}

float Rectangle::pdf(ShadeRec &sr)
{
    return inv_area;
}

Normal Rectangle::getNormal(const Point3D &p) const
{
    return normal;
}
