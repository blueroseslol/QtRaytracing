#include "rectangle.h"

Rectangle::Rectangle():Geometry()
{

}

Rectangle::Rectangle(Point3D _p0, Vector3D _a, Vector3D _b, Normal _normal):Geometry(),p0(_p0),a(_a),b(_b),normal(_normal)
{

}

Point3D Rectangle::sampler()
{
    Point2D sample_point=sampler_ptr->sampleUnitSquare();
    return p0+sample_point.x*a+sample_point.y*b;
}

Normal Rectangle::getNormal(const Point3D &p) const
{
    return normal;
}
