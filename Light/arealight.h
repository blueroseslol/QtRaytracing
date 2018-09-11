#ifndef AREALIGHT_H
#define AREALIGHT_H
#include "Light/light.h"
#include "Geometry/Geometry.h"
class AreaLight : public Light
{
public:
    AreaLight();

    AreaLight(const AreaLight& al);

    AreaLight(AreaLight&& al);

    void setLocation(const Point3D &_location);

    void setLocation(const float& x,const float& y,const float& z );

    void setObject(Geometry* objectPtr);

    virtual Vector3D getDirection(ShadeRec &sr);

    virtual RGBColor L(ShadeRec& sr);

    virtual bool inShadow(const Ray& ray,const ShadeRec& sr) const;

    virtual float G(const ShadeRec& sr) const;

    virtual float pdf(const ShadeRec& sr) const;
private:
    Geometry* object_ptr;
    Material* material_ptr;
    Point3D samplerPoint;
    Normal lightNormal;
    Vector3D wi;
};

#endif // AREALIGHT_H
