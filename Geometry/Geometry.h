#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "Utilities/ShadeRec.h"
#include "Utilities/Ray.h"
#include "Utilities/RGBColor.h"
class Material;

class Geometry
{
public:
    Geometry();

    ~Geometry();
    virtual bool hit(const Ray& ray,double& tmin,ShadeRec& sr) const =0;

    RGBColor getColor() const;
    void setColor(const RGBColor &_color);

    virtual void setMaterial(Material* mPtr);

    virtual bool shadowHit(const Ray& ray,float& tMin) const=0;

    virtual Point3D sampler()=0;

    Material* getMaterial() const;
protected:
    RGBColor color;
    mutable Material* material_ptr;
};

#endif
