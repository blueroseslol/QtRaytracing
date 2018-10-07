#include "PerfectTransmitter.h"

PerfectTransmitter::PerfectTransmitter():BTDF(),
    kt(0.0),ior(1.0)
{}

PerfectTransmitter::PerfectTransmitter(const PerfectTransmitter& pt):BTDF(pt),
    kt(pt.kt),ior(pt.ior)
{}

PerfectTransmitter::PerfectTransmitter(PerfectTransmitter &&pt):BTDF(pt),
    kt(pt.kt),ior(pt.ior)
{}

PerfectTransmitter::~PerfectTransmitter() {}

bool PerfectTransmitter::tir(const ShadeRec& sr) const {
    Vector3D wo(-sr.ray.direction);
	float cos_thetai = sr.normal * wo;  
	float eta = ior;
	
	if (cos_thetai < 0.0) 
		eta = 1.0 / eta; 
		
	return (1.0 - (1.0 - cos_thetai * cos_thetai) / (eta * eta) < 0.0);
}	

RGBColor PerfectTransmitter::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
    return RGBColor();
}


// ------------------------------------------------------------------- sample_f
// this computes the direction wt for perfect transmission
// and returns the transmission coefficient
// this is only called when there is no total internal reflection

RGBColor PerfectTransmitter::sampleF(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const {
	
	Normal n(sr.normal);
	float cos_thetai = n * wo;
	float eta = ior;	
		
	if (cos_thetai < 0.0) {			// transmitted ray is outside     
		cos_thetai = -cos_thetai;
		n = -n;  					// reverse direction of normal
		eta = 1.0 / eta; 			// invert ior 
	}

	float temp = 1.0 - (1.0 - cos_thetai * cos_thetai) / (eta * eta);
	float cos_theta2 = sqrt(temp);
	wt = -wo / eta - (cos_theta2 - cos_thetai / eta) * n;   
	
	// P570  Formula 27.9
    return (kt / (eta * eta) * RGBColor(1,1,1) / fabs(sr.normal * wt));
}


// ------------------------------------------------------------------- rho

RGBColor PerfectTransmitter::rho(const ShadeRec& sr, const Vector3D& wo) const {
    return RGBColor();
}
