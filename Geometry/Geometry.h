#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "Utilities/ShadeRec.h"
#include "Utilities/Ray.h"
#include "Utilities/RGBColor.h"
#include "Utilities/BBox.h"
class Material;

class Geometry
{
public:
    Geometry();

    ~Geometry();
    virtual bool hit(const Ray& ray,double& tmin,ShadeRec& sr) const;

    RGBColor getColor() const;
    void setColor(const RGBColor &_color);

    virtual void setMaterial(Material* mPtr);

    virtual bool shadowHit(const Ray& ray,double &tmin) const;

    virtual Point3D sampler();

    virtual float pdf(const ShadeRec &sr) const;

    Material* getMaterial() const;

    virtual Normal getNormal(const Point3D& point) const;

    virtual BBox getBoundingBox();

    bool castShadow;
protected:
    RGBColor color;
    mutable Material* material_ptr;
};

#endif
