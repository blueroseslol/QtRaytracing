#ifndef __PERFECT_SPECULAR__
#define __PERFECT_SPECULAR__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// this implements perfect specular reflection for indirect illumination
// with reflective materials 

#include "BRDF.h"
#include "Utilities/Normal.h"

class PerfectSpecular: public BRDF 
{
	public:
        PerfectSpecular();
		
        ~PerfectSpecular();

        PerfectSpecular(const PerfectSpecular& ps);

        PerfectSpecular(PerfectSpecular&& ps);

		void setSamples(const int numSamples);
		
        void setKr(const float k);
		
        void setCr(const RGBColor& c);
		
        void setCr(const float r, const float g, const float b);
		
        void setCr(const float c);
		
        virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
		
        virtual RGBColor sampleF(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const;
		
        virtual RGBColor sampleF(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;
		
        virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;
	private:
		float		kr;			// reflection coefficient
		RGBColor 	cr;			// the reflection colour
};

inline void PerfectSpecular::setKr(const float k) {
	kr = k;
}

inline void PerfectSpecular::setCr(const RGBColor& c) {
	cr = c;
}

inline void	PerfectSpecular::setCr(const float r, const float g, const float b) {
	cr.r = r; cr.g = g; cr.b = b;
}

inline void	PerfectSpecular::setCr(const float c) {
	cr.r = c; cr.g = c; cr.b = c;
}

#endif

