#include "rectangle.h"

Rectangle::Rectangle()
{

}

Point3D Rectangle::sampler()
{
    Point2D sample_point=sampler_ptr->sampleUnitSquare();
    return p0+sample_point.x*a+sample_point.y*b;
}
