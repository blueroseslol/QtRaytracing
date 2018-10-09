#ifndef __SV_LAMBERTIAN__
#define __SV_LAMBERTIAN__

#include "BRDF/BRDF.h"
#include "Texture/Texture.h"

class SV_Lambertian : public BRDF {
public:
    SV_Lambertian();

	SV_Lambertian(const SV_Lambertian& lamb);

    SV_Lambertian(SV_Lambertian&& lamb);

    void setCd(Texture* tex);

    void setKd(const float value);

    ~SV_Lambertian();

    virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;

    virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

    virtual RGBColor sampleF(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

private:
    float	kd;
    Texture* cd;
};

inline void SV_Lambertian::setKd(const float value){
	kd = value;
}
#endif
