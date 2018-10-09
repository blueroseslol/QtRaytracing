#include "SV_Lambertian.h"
#include "Utilities/Constants.h"

SV_Lambertian::SV_Lambertian(): BRDF(),
kd(0.0),
cd(nullptr)
{}


SV_Lambertian::SV_Lambertian(const SV_Lambertian& lamb): BRDF(lamb),
kd(lamb.kd),
cd(lamb.cd)
{}

SV_Lambertian::SV_Lambertian(SV_Lambertian &&lamb): BRDF(lamb),
kd(lamb.kd),
cd(lamb.cd)
{}

SV_Lambertian::~SV_Lambertian() {}

void SV_Lambertian::setCd(Texture* tex){
	cd = tex;
}

RGBColor SV_Lambertian::rho(const ShadeRec& sr, const Vector3D& wo) const {
    return (kd * cd->getColor(sr));
}

RGBColor SV_Lambertian::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
    return (kd * cd->getColor(sr) * invPI);
}

RGBColor SV_Lambertian::sampleF(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const {

	Vector3D w = sr.normal;
	Vector3D v = Vector3D(0.0034, 1, 0.0071) ^ w;
	v.normalize();
	Vector3D u = v ^ w;

    Point3D sp = sampler_ptr->sampleHemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;
	wi.normalize();

	pdf = sr.normal * wi * invPI;

	//return (kd * cd * invPI);
    return (kd * cd->getColor(sr) * invPI);
}
