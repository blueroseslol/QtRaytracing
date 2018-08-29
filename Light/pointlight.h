#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "Light/light.h"

class PointLight : public Light
{
public:
    PointLight();

    PointLight(const PointLight& pointLight);

    PointLight(PointLight&& pointLight);

    void setLocation(const Point3D &_location);

    void setLocation(const float& x,const float& y,const float& z );

    void setColor(const RGBColor& _color);

    void setColor(const float& x,const float& y,const float& z);

    virtual Vector3D getDirection(ShadeRec &sr);

    virtual RGBColor	 L(ShadeRec& sr);

    virtual bool inShadow(const Ray &ray, const ShadeRec &sr) const;
private:
    float ls;
    RGBColor color;
    Point3D location;
};

inline void PointLight::setLocation(const Point3D &_location)
{
    location=_location;
}

inline void PointLight::setLocation(const float &x, const float &y, const float &z)
{
    location=Point3D(x,y,z);
}

inline void PointLight::setColor(const RGBColor &_color)
{
    color=_color;
}

inline void PointLight::setColor(const float &x, const float &y, const float &z)
{
    color=RGBColor(x,y,z);
}
#endif // POINTLIGHT_H
