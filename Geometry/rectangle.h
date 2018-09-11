﻿#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Geometry/Geometry.h"
#include "Sampler/sampler.h"
class Rectangle : public Geometry
{
public:
    Rectangle();

    Rectangle(Point3D _p0,Vector3D _a,Vector3D _b,Normal _normal);

    virtual bool hit(const Ray &ray, double &tmin, ShadeRec &sr) const;

    virtual bool shadowHit(const Ray &ray, float &tMin) const;

    void setSampler(Sampler *sampler);

    virtual Point3D sampler();

    virtual float pdf(ShadeRec& sr);

    virtual Normal getNormal(const Point3D& p) const override;
private:
    Point3D p0;
    Vector3D a;
    Vector3D b;
    Normal normal;
    Sampler *sampler_ptr;
    float inv_area;
};

#endif // RECTANGLE_H
