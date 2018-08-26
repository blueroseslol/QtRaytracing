#include "glossyspecular.h"

GlossySpecular::GlossySpecular()
{

}

GlossySpecular::GlossySpecular(const GlossySpecular &brdf)
{

}

GlossySpecular::GlossySpecular(GlossySpecular &&brdf)
{

}

RGBColor GlossySpecular::f(const ShadeRec &sr, const Vector3D &wi, const Vector3D &wo) const
{
    RGBColor L;
    float ndotwi=sr.normal*wi;
    Vector3D r(-wi+2.0*sr.normal*ndotwi);
    float rdotwo=r*wo;
    if(rdotwo>0)
        l=ka*pow(rdotwo,exp);
    return L;
}

RGBColor GlossySpecular::rho(const ShadeRec &sr, const Vector3D &wo) const
{

}

RGBColor GlossySpecular::sample_f(const ShadeRec &sr, Vector3D &wi, const Vector3D &wo) const
{

}
