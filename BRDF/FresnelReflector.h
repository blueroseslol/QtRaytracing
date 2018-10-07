#ifndef __FRESNEL_REFLECTOR__
#define __FRESNEL_REFLECTOR__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "BRDF.h"
#include "Utilities/Normal.h"

class FresnelReflector : public BRDF
{
public:

    FresnelReflector();

    ~FresnelReflector();

    FresnelReflector(const FresnelReflector& fr);

    FresnelReflector(FresnelReflector&& fr);
	
    virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
	

    virtual RGBColor sampleF(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const;

	/*
	virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;
	*/

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;

	float fresnel(const ShadeRec& sr) const;

    void setEtaIn(float value);

    void setEtaOut(float value);

private:
	float eta_in;
	float eta_out;
};


inline void FresnelReflector::setEtaIn(float value){
	eta_in = value;
}

inline void FresnelReflector::setEtaOut(float value){
	eta_out = value;
}

#endif
