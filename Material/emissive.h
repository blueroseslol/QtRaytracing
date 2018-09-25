#ifndef EMISSIVE_H
#define EMISSIVE_H
#include "Material/material.h"

class Emissive : public Material
{
public:
    Emissive();

    void scaleRadiance(const float _ls);

    void setCe(const float& r,const float& g,const float& b);

    virtual RGBColor getLe(ShadeRec& sr) const;

    virtual RGBColor shade(ShadeRec& sr);

    virtual RGBColor areaLightShade(ShadeRec& sr);
private:
    float ls;
    RGBColor ce;    //自发光颜色
};

#endif // EMISSIVE_H
