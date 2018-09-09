#ifndef __MATTE__
#define __MATTE__

#include "Material.h"
#include "BRDF/Lambertian.h"

class Matte: public Material {	
public:
        Matte();

		Matte(const Matte& m);

        Matte(Matte&& m);
		
//        virtual Material*	clone(void) const;

//		Matte& operator= (const Matte& rhs);

        ~Matte();
		
        void 	setKa(const float k);
		
        void 	setKd(const float k);
		
        void	setCd(const RGBColor c);
		
        void	setCd(const float r, const float g, const float b);
		
        void	setCd(const float c);
				
        virtual RGBColor	shade(ShadeRec& sr);

        RGBColor areaLightShade(ShadeRec &sr);
private:
		Lambertian*		ambient_brdf;
		Lambertian*		diffuse_brdf;
};

inline void	Matte::setKa(const float ka) {
    ambient_brdf->setKd(ka);
}

inline void	Matte::setKd (const float kd) {
    diffuse_brdf->setKd(kd);
}

inline void	Matte::setCd(const RGBColor c) {
    ambient_brdf->setCd(c);
    diffuse_brdf->setCd(c);
}

inline void	Matte::setCd(const float r, const float g, const float b) {
    ambient_brdf->setCd(r, g, b);
    diffuse_brdf->setCd(r, g, b);
}

inline void	Matte::setCd(const float c) {
    ambient_brdf->setCd(c);
    diffuse_brdf->setCd(c);
}

#endif
