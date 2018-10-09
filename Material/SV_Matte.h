#ifndef __SV_MATTE__
#define __SV_MATTE__

#include "Material.h"
#include "BRDF/SV_Lambertian.h"

class SV_Matte : public Material {
public:
    SV_Matte();

	SV_Matte(const SV_Matte& m);

    SV_Matte(SV_Matte&& m);

    ~SV_Matte();

    void setCd(Texture* t_ptr);

    void setKa(const float k);

    void setKd(const float k);

    virtual RGBColor shade(ShadeRec& s);
private:
	SV_Lambertian*	ambient_brdf;
	SV_Lambertian*	diffuse_brdf;
};


inline void SV_Matte::setCd(Texture* t_ptr) {
	ambient_brdf->setCd(t_ptr);
	diffuse_brdf->setCd(t_ptr);
}

inline void SV_Matte::setKa(const float ka) {
	ambient_brdf->setKd(ka);
}

inline void SV_Matte::setKd(const float k){
	diffuse_brdf->setKd(k);
}
#endif
