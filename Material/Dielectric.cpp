#include "Dielectric.h"
#include "Tracer/tracer.h"

Dielectric::Dielectric()
: Phong(),
fresnel_reflector_brdf(new FresnelReflector),
fresnel_transmitter_btdf(new FresnelTransmitter)
{}

Dielectric::Dielectric(const Dielectric& rm):Phong(rm),
fresnel_reflector_brdf(new std::remove_pointer<decltype(rm.fresnel_reflector_brdf)>::type (*rm.fresnel_reflector_brdf)),
fresnel_transmitter_btdf(new std::remove_pointer<decltype(rm.fresnel_transmitter_btdf)>::type (*rm.fresnel_transmitter_btdf))
{

}

Dielectric::Dielectric(Dielectric &&rm):Phong(rm),
fresnel_reflector_brdf(rm.fresnel_reflector_brdf),fresnel_transmitter_btdf(rm.fresnel_transmitter_btdf)
{
    rm.fresnel_reflector_brdf=nullptr;
    rm.fresnel_transmitter_btdf=nullptr;
}

Dielectric::~Dielectric() {
	if (fresnel_reflector_brdf) {
		delete fresnel_reflector_brdf;
        fresnel_reflector_brdf = nullptr;
	}

	if (fresnel_transmitter_btdf){
		delete fresnel_transmitter_btdf;
        fresnel_transmitter_btdf = nullptr;
	}
}

RGBColor Dielectric::shade(ShadeRec& sr) {
	RGBColor L(Phong::shade(sr));

	Vector3D 	wi;
    Vector3D 	wo(-sr.ray.direction);
    RGBColor 	fr = fresnel_reflector_brdf->sampleF(sr, wo, wi);  	// computes wi
	Ray 		reflected_ray(sr.hit_point, wi);
	double 		t = 0;
	RGBColor 	Lr, Lt;
	float 		ndotwi = sr.normal * wi;

	if (fresnel_transmitter_btdf->tir(sr)) {								// total internal reflection
		if (ndotwi < 0.0) {
			// reflected ray is inside

			Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);
			L += cf_in.powc(t) * Lr;   						// inside filter color
		}
		else {
			// reflected ray is outside

			Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);   // kr = 1  
			L += cf_out.powc(t) * Lr;   					// outside filter color
		}
	}
	else { 													// no total internal reflection
		Vector3D wt;
        RGBColor ft = fresnel_transmitter_btdf->sampleF(sr, wo, wt);  	// computes wt
		Ray transmitted_ray(sr.hit_point, wt);
		float ndotwt = sr.normal * wt;

		if (ndotwi < 0.0) {
			// reflected ray is inside

			Lr = fr * sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1) * fabs(ndotwi);
			L += cf_in.powc(t) * Lr;     					// inside filter color

			// transmitted ray is outside

			Lt = ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1) * fabs(ndotwt);
			L += cf_out.powc(t) * Lt;   					// outside filter color
		}
		else {
			// reflected ray is outside

			Lr = fr * sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1) * fabs(ndotwi);
			L += cf_out.powc(t) * Lr;						// outside filter color

			// transmitted ray is inside

			Lt = ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1) * fabs(ndotwt);
			L += cf_in.powc(t) * Lt; 						// inside filter color
		}
	}

    return L;
}

void Dielectric::setEtaIn(float value){
    fresnel_reflector_brdf->setEtaIn(value);
    fresnel_transmitter_btdf->setEtaIn(value);
}

void Dielectric::setEtaOut(float value){
    fresnel_reflector_brdf->setEtaOut(value);
    fresnel_transmitter_btdf->setEtaOut(value);
}
