#include "FresnelTransmitter.h"

FresnelTransmitter::FresnelTransmitter()
: BTDF(),eta_in(1.0f),eta_out(1.0f)
{}


// ------------------------------------------------------------------- copy constructor

FresnelTransmitter::FresnelTransmitter(const FresnelTransmitter& pt):
BTDF(pt),eta_in(pt.eta_in),eta_out(pt.eta_out)
{}

FresnelTransmitter::FresnelTransmitter(FresnelTransmitter &&pt):
BTDF(pt),eta_in(pt.eta_in),eta_out(pt.eta_out)
{}

FresnelTransmitter::~FresnelTransmitter() {}

bool FresnelTransmitter::tir(const ShadeRec& sr) const {
    Vector3D wo(-sr.ray.direction);
	float cos_thetai = sr.normal * wo;
	//float eta = ior;
	float eta = eta_in / eta_out;

	if (cos_thetai < 0.0)
		eta = 1.0 / eta;

	return (1.0 - (1.0 - cos_thetai * cos_thetai) / (eta * eta) < 0.0);
}

RGBColor
FresnelTransmitter::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
    return RGBColor();
}


RGBColor
FresnelTransmitter::sampleF(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const {

	Normal n(sr.normal);
	float cos_thetai = n * wo;
	//float eta = ior;
	float eta = eta_in / eta_out;

	if (cos_thetai < 0.0) {			// transmitted ray is outside     
		cos_thetai = -cos_thetai;
		n = -n;  					// reverse direction of normal
		eta = 1.0 / eta; 			// invert ior 
	}

	float temp = 1.0 - (1.0 - cos_thetai * cos_thetai) / (eta * eta);
	float cos_theta2 = sqrt(temp);
	wt = -wo / eta - (cos_theta2 - cos_thetai / eta) * n;

	// P570  Formula 27.9
	//return (kt / (eta * eta) * white / fabs(sr.normal * wt));
    return fresnel(sr) / (eta * eta) * RGBColor(1) / fabs(sr.normal * wt);
}


RGBColor
FresnelTransmitter::rho(const ShadeRec& sr, const Vector3D& wo) const {
    return RGBColor();
}

float
FresnelTransmitter::fresnel(const ShadeRec& sr) const {
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
	float kt = 1 - kr;
    return kt;
}
