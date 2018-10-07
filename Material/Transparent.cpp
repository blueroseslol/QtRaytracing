#include "Transparent.h"
#include "Tracer/tracer.h"
// ---------------------------------------------------------------- default constructor

Transparent::Transparent():Phong(),
    reflective_brdf(new PerfectSpecular),specular_btdf(new PerfectTransmitter)
{}


// ---------------------------------------------------------------- copy constructor

Transparent::Transparent(const Transparent& rm):Phong(rm),
reflective_brdf(new std::remove_pointer<decltype(rm.reflective_brdf)>::type (*rm.reflective_brdf)),
specular_btdf(new std::remove_pointer<decltype(rm.specular_btdf)>::type (*rm.specular_btdf))
{}

Transparent::Transparent(Transparent &&rm):Phong(rm),
reflective_brdf(rm.reflective_brdf),specular_btdf(rm.specular_btdf)
{
    rm.reflective_brdf=nullptr;
    rm.specular_btdf=nullptr;
}

Transparent::~Transparent() {
    if (reflective_brdf) {
        delete reflective_brdf;
        reflective_brdf = nullptr;
    }

    if (specular_btdf){
        delete specular_btdf;
        specular_btdf = nullptr;
    }
}

RGBColor Transparent::shade(ShadeRec& sr) {
    RGBColor L(Phong::shade(sr));  // direct illumination

    Vector3D wo = -sr.ray.direction;
    Vector3D wi;
    // sample_f calculate wi
    RGBColor fr = reflective_brdf->sampleF(sr, wo, wi);
    Ray reflected_ray(sr.hit_point, wi);

    if (specular_btdf->tir(sr)){
        // kr = 1.0
        L += sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1);
    }
    else{
        Vector3D wt;
        RGBColor ft = specular_btdf->sampleF(sr, wo, wt);
        Ray transmitted_ray(sr.hit_point, wt);

        L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * fabs(sr.normal * wi);

        L += ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, sr.depth + 1) * fabs(sr.normal * wt);
    }


    return L;
}
