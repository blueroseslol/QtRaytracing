#include "lambertian.h"
#include "Utilities/Constants.h"
Lambertian::Lambertian()
{

}

RGBColor Lambertian::f(const ShadeRec &sr, const Vector3D &wi, const Vector3D &wo) const
{
    return kd*cd*invPI;
}

RGBColor Lambertian::sample_f(const ShadeRec &sr, Vector3D &wi, const Vector3D &wo) const
{
    return RGBColor();
}

RGBColor Lambertian::rho(const ShadeRec &sr, const Vector3D &wo) const
{
    return kd*cd;
}
