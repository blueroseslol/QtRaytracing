#ifndef __AMBIENT__
#define __AMBIENT__

#include "Light.h"

class Ambient: public Light {
	public:
	
		Ambient(void);   							

		Ambient(const Ambient& a); 					 

        Ambient(Ambient&& a);
//		virtual Light*
//		clone(void) const;
		
		Ambient& 									
		operator= (const Ambient& rhs);									
		
		virtual 									
        ~Ambient();
				
		void
                scaleRadiance(const float b);
		
		void
                setColor(const float c);
		
		void
                setColor(const RGBColor& c);
		
		void
                setColor(const float r, const float g, const float b);
		
		virtual Vector3D								
		getDirection(ShadeRec& s); 
		
		virtual RGBColor
		L(ShadeRec& s);
	
	private:
	
		float		ls;
		RGBColor	color;
};




// ------------------------------------------------------------------------------- scale_radiance

inline void
Ambient::scaleRadiance(const float b) {
	ls = b;
}

// ------------------------------------------------------------------------------- set_color

inline void
Ambient::setColor(const float c) {
	color.r = c; color.g = c; color.b = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
Ambient::setColor(const RGBColor& c) {
	color = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
Ambient::setColor(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}


#endif
