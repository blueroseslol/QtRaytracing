#include "SV_Matte.h"

SV_Matte::SV_Matte(): Material(),
ambient_brdf(new SV_Lambertian),
diffuse_brdf(new SV_Lambertian)
{}

SV_Matte::SV_Matte(const SV_Matte& m): Material(m),
    ambient_brdf(new std::remove_pointer<decltype(m.ambient_brdf)>::type (*m.ambient_brdf)),
    diffuse_brdf(new std::remove_pointer<decltype(m.diffuse_brdf)>::type (*m.diffuse_brdf))
{

}

SV_Matte::SV_Matte(SV_Matte &&m):Material(m),
    ambient_brdf(m.ambient_brdf),diffuse_brdf(m.diffuse_brdf)
{
    ambient_brdf=nullptr;
    diffuse_brdf=nullptr;
}

SV_Matte::~SV_Matte() {
	if (ambient_brdf) {
		delete ambient_brdf;
        ambient_brdf = nullptr;
	}
	if (diffuse_brdf) {
		delete diffuse_brdf;
        diffuse_brdf = nullptr;
	}
}

// book

RGBColor
SV_Matte::shade(ShadeRec& sr) {
    Vector3D 	wo = -sr.ray.direction;
	RGBColor 	L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);

    for (int j = 0; j <sr.w.lights.size(); j++) {
		Light* light_ptr = sr.w.lights[j];
        Vector3D wi = light_ptr->getDirection(sr);
		wi.normalize();
		float ndotwi = sr.normal * wi;
		float ndotwo = sr.normal * wo;

		if (ndotwi > 0.0 && ndotwo > 0.0) {
			bool in_shadow = false;

            if (sr.w.lights[j]->castShadow) {
				Ray shadow_ray(sr.hit_point, wi);
                in_shadow = light_ptr->inShadow(shadow_ray, sr);
			}

			if (!in_shadow)
				L += diffuse_brdf->f(sr, wo, wi) * light_ptr->L(sr) * light_ptr->G(sr) * ndotwi;
		}
	}

	return (L);
}


// my
//RGBColor
//SV_Matte::shade(ShadeRec& sr) {
//	Vector3D 	wo = -sr.ray.d;
//	RGBColor 	L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);


//	for (int j = 0; j < sr.w.lights.size(); j++) {
//		Vector3D wi = sr.w.lights[j]->get_direction(sr);
//		float ndotwi = sr.normal * wi;

//		if (ndotwi > 0.0){
//			if (shadows){
//				bool in_shadows = false;

//				if (sr.w.lights[j]->casts_shadows()){
//					Ray shadowRay(sr.hit_point, wi);
//					in_shadows = sr.w.lights[j]->in_shadow(shadowRay, sr);
//				}

//				if (!in_shadows){
//					L += diffuse_brdf->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * ndotwi;
//				}
//			}
//			else{
//				L += diffuse_brdf->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * ndotwi;
//			}

//		}
//	}

//	return (L);
//}
