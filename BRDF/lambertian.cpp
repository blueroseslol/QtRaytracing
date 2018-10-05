#include "lambertian.h"
#include "Utilities/Constants.h"
#include "Sampler/multijittered.h"
Lambertian::Lambertian():BRDF(),kd(0),cd(0)
{

}

Lambertian::Lambertian(const Lambertian &lambertian):BRDF(lambertian),kd(lambertian.kd),cd(lambertian.cd)
{

}

Lambertian::Lambertian(Lambertian &&lambertian):BRDF(lambertian),kd(lambertian.kd),cd(lambertian.cd)
{

}

RGBColor Lambertian::f(const ShadeRec &sr, const Vector3D &wo, const Vector3D &wi) const
{
    return kd*cd*invPI;
}

RGBColor Lambertian::sampleF(const ShadeRec &sr, Vector3D &wo, const Vector3D &wi) const
{
    return RGBColor();
}

RGBColor Lambertian::sampleF(const ShadeRec &sr, const Vector3D &wo, Vector3D &wi, float &pdf) const
{
    Vector3D w = sr.normal;
    Vector3D v = Vector3D(0.00424, 1, 0.00764) ^ w;
    v.normalize();
    Vector3D u = v ^ w;

    Point3D sp = sampler_ptr->sampleHemisphere();
    wi = sp.x * u + sp.y * v + sp.z * w;
    wi.normalize();
    pdf = sr.normal*wi*invPI;
    return kd * cd * invPI;
}

RGBColor Lambertian::rho(const ShadeRec &sr, const Vector3D &wo) const
{
    return kd*cd;
}

void Lambertian::setSamples(const int numSamples)
{
    sampler_ptr=new MultiJittered(numSamples);
    sampler_ptr->map_samples_to_hemisphere(1.0);
}
