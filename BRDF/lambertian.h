#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H
#include "BRDF/brdf.h"

class Lambertian : public BRDF
{
public:
    Lambertian();

    virtual RGBColor f(const ShadeRec &sr, const Vector3D &wi, const Vector3D &wo) const;

    virtual RGBColor sample_f(const ShadeRec &sr, Vector3D &wi, const Vector3D &wo) const;

    virtual RGBColor rho(const ShadeRec &sr, const Vector3D &wo) const;
private:
    float kd;
    RGBColor cd;
};

#endif // LAMBERTIAN_H
