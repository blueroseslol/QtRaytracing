#include "brdf.h"

BRDF::BRDF():sampler_ptr(nullptr)
{

}

BRDF::~BRDF()
{
    if(sampler_ptr)
    {
        delete sampler_ptr;
        sampler_ptr=nullptr;
    }
}

RGBColor BRDF::sampleF(const ShadeRec &sr, Vector3D &wi, const Vector3D &wo) const
{
    return RGBColor(1.0);
}

RGBColor BRDF::sampleF(const ShadeRec &sr, const Vector3D &wo, Vector3D &wi, float &pdf) const
{
    return RGBColor(1.0);
}
