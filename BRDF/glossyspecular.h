#ifndef GLOSSYSPECULAR_H
#define GLOSSYSPECULAR_H
#include "BRDF/brdf.h"

class GlossySpecular:BRDF
{
public:
    GlossySpecular();

    GlossySpecular(const GlossySpecular& brdf);

    GlossySpecular(GlossySpecular&& brdf);

    virtual RGBColor f(const ShadeRec &sr, const Vector3D &wo, const Vector3D &wi) const;

    virtual RGBColor rho(const ShadeRec &sr, const Vector3D &wo) const;

    virtual RGBColor sample_f(const ShadeRec &sr, Vector3D &wo, const Vector3D &wi) const;

    void setKs(const float k);
    void setCs(const RGBColor &c);
    void setCs(const float r, const float g, const float b);
    void setCs(const float c);
    void setExp(const float e);
private:
    float ks;
    RGBColor cs;
    float exp;
};

inline void GlossySpecular::setKs(const float k)
{
    ks=k;
}

inline void GlossySpecular::setCs(const RGBColor &c)
{
    cs=c;
}

inline void GlossySpecular::setCs(const float r, const float g, const float b)
{
    cs=RGBColor(r,g,b);
}

inline void GlossySpecular::setCs(const float c)
{
    cs=RGBColor(c);
}

inline void GlossySpecular::setExp(const float e)
{
    exp=e;
}

#endif // GLOSSYSPECULAR_H
