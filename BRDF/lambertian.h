#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H
#include "BRDF/brdf.h"

class Lambertian : public BRDF
{
public:
    Lambertian();

    Lambertian(const Lambertian& lambertian);

    Lambertian(Lambertian&& lambertian);

    virtual RGBColor f(const ShadeRec &sr, const Vector3D &wi, const Vector3D &wo) const;

    virtual RGBColor sample_f(const ShadeRec &sr, Vector3D &wi, const Vector3D &wo) const;

    virtual RGBColor rho(const ShadeRec &sr, const Vector3D &wo) const;

    void setKa(const float k);
    void setKd(const float k);
    void setCd(const RGBColor &c);
    void setCd(const float r, const float g, const float b);
    void setCd(const float c);
private:
    float kd;
    RGBColor cd;
};

// -------------------------------------------------------------- set_ka

inline void
Lambertian::setKa(const float k) {
    kd = k;
}



// -------------------------------------------------------------- set_kd

inline void
Lambertian::setKd(const float k) {
    kd = k;
}


// -------------------------------------------------------------- set_cd

inline void
Lambertian::setCd(const RGBColor& c) {
    cd = c;
}


// ---------------------------------------------------------------- set_cd

inline void
Lambertian::setCd(const float r, const float g, const float b) {
    cd.r = r; cd.g = g; cd.b = b;
}


// ---------------------------------------------------------------- set_cd

inline void
Lambertian::setCd(const float c) {
    cd.r = c; cd.g = c; cd.b = c;
}
#endif // LAMBERTIAN_H
