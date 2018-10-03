#include "Reflective.h"
#include "Tracer/tracer.h"

Reflective::Reflective ():Phong(),reflective_brdf(new PerfectSpecular)
{}

Reflective::Reflective(const Reflective& rm):Phong(rm),
    reflective_brdf(new std::remove_pointer<decltype(rm.reflective_brdf)>::type (*rm.reflective_brdf))
{}

Reflective::Reflective(Reflective &&rm):Phong(rm),reflective_brdf(rm.reflective_brdf)
{
    rm.reflective_brdf=nullptr;
}

Reflective::~Reflective() {
    if (reflective_brdf) {
        delete reflective_brdf;
        reflective_brdf = nullptr;
    }
}

RGBColor Reflective::shade(ShadeRec& sr) {
    RGBColor L(Phong::shade(sr));  // direct illumination

    Vector3D wo = -sr.ray.direction;
    Vector3D wi;
    RGBColor fr = reflective_brdf->sampleF(sr, wo, wi);
    Ray reflected_ray(sr.hit_point, wi);
//    reflected_ray.depth = sr.depth + 1;
    L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi);

    return L;
}
