#ifndef __DIRECTIONAL__
#define __DIRECTIONAL__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Light.h"
#include "Utilities/Vector3D.h"
#include "Utilities/RGBColor.h"

#include "World.h"			// you will need this later on for shadows
#include "Utilities/ShadeRec.h"


class Directional: public Light {
	public:
	
        Directional();

		Directional(const Directional& dl); 

        Directional(Directional&& dl);
//		virtual Light*
//		clone(void) const;

//		Directional&
//		operator= (const Directional& rhs);
			
		virtual											
        ~Directional();
				
		void
        scaleRadiance(const float b);
		
		void
        setColor(const float c);
		
		void
        setColor(const RGBColor& c);
		
		void
        setColor(const float r, const float g, const float b);
			
		void
        setDirection(Vector3D d);
		
		void
        setDirection(float dx, float dy, float dz);
		
        virtual Vector3D	getDirection(ShadeRec& sr);
				
        virtual RGBColor L(ShadeRec& sr);
		
        virtual bool inShadow(const Ray &ray, const ShadeRec &sr) const;
	private:
		float		ls;			
		RGBColor	color;
		Vector3D	dir;		// direction the light comes from
};


// inlined access functions


// ------------------------------------------------------------------------------- scale_radiance

inline void
Directional::scaleRadiance(const float b) {
	ls = b;
}

// ------------------------------------------------------------------------------- set_color

inline void
Directional::setColor(const float c) {
	color.r = c; color.g = c; color.b = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
Directional::setColor(const RGBColor& c) {
	color = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
Directional::setColor(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}


// ---------------------------------------------------------------------- set_direction

inline void
Directional::setDirection(Vector3D d) {
	dir = d;
	dir.normalize();
}


// ---------------------------------------------------------------------- set_direction 

inline void
Directional::setDirection(float dx, float dy, float dz) {
	dir.x = dx; dir.y = dy; dir.z = dz;
	dir.normalize();
}


#endif

