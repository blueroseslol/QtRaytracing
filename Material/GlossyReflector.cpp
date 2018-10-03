#include "GlossyReflector.h"
#include "Tracer/tracer.h"
GlossyReflector::GlossyReflector()
: Phong(),glossy_specular_brdf(new GlossySpecular)
{}

GlossyReflector::GlossyReflector(const GlossyReflector& rm)
: Phong(rm),glossy_specular_brdf(new std::remove_pointer<decltype(rm.glossy_specular_brdf)>::type (*rm.glossy_specular_brdf)) {

}

GlossyReflector::GlossyReflector(GlossyReflector &&rm):Phong(rm),glossy_specular_brdf(rm.glossy_specular_brdf)
{
    rm.glossy_specular_brdf=nullptr;
}

GlossyReflector::~GlossyReflector() {
    if (glossy_specular_brdf) {
        delete glossy_specular_brdf;
        glossy_specular_brdf = nullptr;
    }
}

RGBColor GlossyReflector::areaLightShade(ShadeRec& sr) {
    RGBColor 	L(Phong::areaLightShade(sr));  // direct illumination
    Vector3D 	wo(-sr.ray.direction);
    Vector3D 	wi;
    float		pdf;
    RGBColor 	fr(glossy_specular_brdf->sampleF(sr, wo, wi,pdf));
    Ray 		reflected_ray(sr.hit_point, wi);

    L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi) / pdf;

    return L;
}
