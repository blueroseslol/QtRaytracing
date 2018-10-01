#include "glossyspecular.h"

GlossySpecular::GlossySpecular():ks(0),cs(1),exp(1)
{

}

GlossySpecular::GlossySpecular(const GlossySpecular &brdf):BRDF(brdf),
    ks(brdf.ks),cs(brdf.cs),exp(brdf.exp)
{

}

GlossySpecular::GlossySpecular(GlossySpecular &&brdf):BRDF(brdf),
    ks(brdf.ks),cs(brdf.cs),exp(brdf.exp)
{

}

RGBColor GlossySpecular::f(const ShadeRec &sr, const Vector3D &wo, const Vector3D &wi) const
{
//    RGBColor L;
//    float ndotwi=sr.normal*wi;
//    Vector3D r(-wi+2.0*sr.normal*ndotwi);
//    float rdotwo=r*wo;
//    if(ndotwi>0)
//        L=ks*cd*pow(rdotwo,exp);
//    return L;
    RGBColor 	L;
    float 		ndotwi = sr.normal * wi;
    Vector3D 	r(-wi + 2.0 * sr.normal * ndotwi); // mirror reflection direction
    float 		rdotwo = r * wo;

    if (rdotwo > 0.0)
        L = ks * cs * pow(rdotwo, exp);

    return L;
}

RGBColor GlossySpecular::rho(const ShadeRec &sr, const Vector3D &wo) const
{
    return RGBColor();
}

RGBColor GlossySpecular::sampleF(const ShadeRec &sr, Vector3D &wo, const Vector3D &wi) const
{
    return RGBColor();
}
