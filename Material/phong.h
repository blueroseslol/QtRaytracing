#ifndef PHONG_H
#define PHONG_H
#include "Material/material.h"
#include "BRDF/Lambertian.h"
#include "BRDF/glossyspecular.h"

class Phong:public Material
{
public:
    Phong();

    Phong(const Phong& phong);

    Phong(Phong&& phong);

    ~Phong();

    virtual RGBColor shade(ShadeRec& sr);

    void 	setKa(const float k);

    void 	setKd(const float k);

    void	setCd(const RGBColor c);

    void	setCd(const float r, const float g, const float b);

    void	setCd(const float c);

    void setSpecularKs(const float k);

    void setSpecularCd(const RGBColor c);

    void setSpecularCd(const float r,const float g,const float b);

    void setSpecularCd(const float c);

    void setSpecularExp(const float e);
protected:
    Lambertian* ambient_brdf;
    Lambertian* diffuse_brdf;
    GlossySpecular* specular_brdf;
};

inline void Phong::setKa(const float k)
{
    ambient_brdf->setKd(k);
}

inline void Phong::setKd(const float k)
{
    diffuse_brdf->setKd(k);
}

inline void Phong::setCd(const RGBColor c)
{
    ambient_brdf->setCd(c);
    diffuse_brdf->setCd(c);
}

inline void Phong::setCd(const float r, const float g, const float b)
{
    ambient_brdf->setCd(r, g, b);
    diffuse_brdf->setCd(r, g, b);
}

inline void Phong::setCd(const float c)
{
    ambient_brdf->setCd(c);
    diffuse_brdf->setCd(c);
}

inline void Phong::setSpecularKs(const float k)
{
    specular_brdf->setKs(k);
}

inline void Phong::setSpecularCd(const RGBColor c)
{
    specular_brdf->setCs(c);
}

inline void Phong::setSpecularCd(const float r, const float g, const float b)
{
    specular_brdf->setCs(RGBColor(r,g,b));
}

inline void Phong::setSpecularCd(const float c)
{
    specular_brdf->setCs(RGBColor(c));
}

inline void Phong::setSpecularExp(const float e)
{
    specular_brdf->setExp(e);
}

#endif // PHONG_H
