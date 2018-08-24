#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "Light/light.h"

class PointLight : public Light
{
public:
    PointLight();

    PointLight(const PointLight& pointLight);

    PointLight(PointLight&& pointLight);

    void setLocation(const Vector3D &_location);

    void setLocation(const float& x,const float& y,const float& z );

    void setColor(const RGBColor& _color);

    void setColor(const float& x,const float& y,const float& z);

    virtual Vector3D getDirection(ShadeRec &sr);

    virtual RGBColor	 L(ShadeRec& sr);
private:
    float ls;
    RGBColor color;
    Vector3D location;
};

inline void PointLight::setLocation(const Vector3D &_location)
{
    location=_location;
}

inline void PointLight::setLocation(const float &x, const float &y, const float &z)
{
    location=Vector3D(x,y,z);
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
