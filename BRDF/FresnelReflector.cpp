// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "FresnelReflector.h"

// ---------------------------------------------------------- default constructor

FresnelReflector::FresnelReflector()
: BRDF(), eta_in(1), eta_out(1)
{}

// ---------------------------------------------------------- destructor

FresnelReflector::~FresnelReflector() {}

FresnelReflector::FresnelReflector(const FresnelReflector &fr):BRDF(fr),
eta_in(fr.eta_in),eta_out(fr.eta_out)
{

}

FresnelReflector::FresnelReflector(FresnelReflector &&fr):BRDF(fr),
eta_in(fr.eta_in),eta_out(fr.eta_out)
{

}

RGBColor FresnelReflector::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
    return RGBColor();
}


// ---------------------------------------------------------- sample_f
// this computes wi: the direction of perfect mirror reflection
// it's called from from the functions Reflective::shade and Transparent::shade.
// the fabs in the last statement is for transparency

RGBColor FresnelReflector::sampleF(const ShadeRec& sr, const Vector3D& wo, Vector3D& wr) const {
	float ndotwo = sr.normal * wo;
	wr = -wo + 2.0 * sr.normal * ndotwo;
    return fresnel(sr) * RGBColor(1) / fabs(sr.normal * wr);
}

// ---------------------------------------------------------- rho

RGBColor FresnelReflector::rho(const ShadeRec& sr, const Vector3D& wo) const {
    return RGBColor();
}


float FresnelReflector::fresnel(const ShadeRec& sr) const {
	Normal normal(sr.normal);
    float ndotd = -normal * sr.ray.direction;
	float eta;

	if (ndotd < 0.0) {
		normal = -normal;
		eta = eta_out / eta_in;
	}
	else
		eta = eta_in / eta_out;

    float cos_theta_i = -normal * sr.ray.direction;
	float temp = 1.0 - (1.0 - cos_theta_i * cos_theta_i) / (eta * eta);
	float cos_theta_t = sqrt(1.0 - (1.0 - cos_theta_i * cos_theta_i) / (eta * eta));
	float r_parallel = (eta * cos_theta_i - cos_theta_t) / (eta * cos_theta_i + cos_theta_t);
	float r_perpendicular = (cos_theta_i - eta * cos_theta_t) / (cos_theta_i + eta * cos_theta_t);
	float kr = 0.5 * (r_parallel * r_parallel + r_perpendicular * r_perpendicular);

    return kr;
}
