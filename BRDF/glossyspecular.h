#ifndef GLOSSYSPECULAR_H
#define GLOSSYSPECULAR_H
#include "BRDF/brdf.h"

class GlossySpecular:BRDF
{
public:
    GlossySpecular();

    GlossySpecular(const GlossySpecular& brdf);

    GlossySpecular(GlossySpecular&& brdf);

    virtual f(const ShadeRec &sr, const Vector3D &wi, const Vector3D &wo) const;

    virtual rho(const ShadeRec &sr, const Vector3D &wo) const;

    virtual sample_f(const ShadeRec &sr, Vector3D &wi, const Vector3D &wo) const;

    void setKa(const float k);
    void setKd(const float k);
    void setKs(const float k);
    void setCd(const RGBColor &c);
    void setCd(const float r, const float g, const float b);
    void setCd(const float c);
private:
    float kd;
    float ks;
    RGBColor cd;
};

#endif // GLOSSYSPECULAR_H
