// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "BTDF.h"

// ------------------------------------------------------------------------ default constructor

BTDF::BTDF() {}


// ------------------------------------------------------------------------ copy constructor

BTDF::BTDF(const BTDF& btdf) {}

BTDF::BTDF(BTDF &&btdf){}

BTDF::~BTDF() {}

RGBColor BTDF::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
    return RGBColor();
}

RGBColor BTDF::sampleF(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const {
    return RGBColor();
}


// ------------------------------------------------------------------------ rho	
	
RGBColor BTDF::rho(const ShadeRec& sr, const Vector3D& wo) const {
    return RGBColor();
}

bool BTDF::tir(const ShadeRec& sr) const{
	return false;
}
