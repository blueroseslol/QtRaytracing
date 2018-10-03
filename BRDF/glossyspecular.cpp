#include "glossyspecular.h"
#include "Sampler/multijittered.h"
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

RGBColor GlossySpecular::sampleF(const ShadeRec &sr, Vector3D &wo, Vector3D &wi, float &pdf) const
{
    float ndotwo = sr.normal * wo;
    Vector3D r = -wo + 2.0 * sr.normal * ndotwo;     // direction of mirror reflection

    Vector3D w = r;
    Vector3D u = Vector3D(0.00424, 1, 0.00764) ^ w;
    u.normalize();
    Vector3D v = u ^ w;

    Point3D sp = sampler_ptr->sampleHemisphere();
    wi = sp.x * u + sp.y * v + sp.z * w;			// reflected ray direction

    if (sr.normal * wi < 0.0) 						// reflected ray is below tangent plane
        wi = -sp.x * u - sp.y * v + sp.z * w;

    float phong_lobe = pow(r * wi, exp);
    pdf = phong_lobe * (sr.normal * wi);

    return (ks * cs * phong_lobe);
}

void GlossySpecular::setSamples(const int numSamples, const float exp)
{
    sampler_ptr=new MultiJittered(numSamples);
    sampler_ptr->map_samples_to_hemisphere(exp);
}
