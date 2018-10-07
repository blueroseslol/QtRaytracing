#ifndef __TRANSPARENT__
#define __TRANSPARENT__

#include "Phong.h"
#include "BRDF/PerfectSpecular.h"
#include "BRDF/PerfectTransmitter.h"

class Transparent: public Phong {	
public:

    Transparent();

    Transparent(const Transparent& rm);

    Transparent(Transparent&& rm);

    ~Transparent();

    void setKr(const float k);

    void setCr(const RGBColor& c);

    void setCr(const float r, const float g, const float b);

    void setCr(const float c);

    void setIor(const float eta);

    void setKt(const float k);

    virtual RGBColor shade(ShadeRec& s);

    //virtual RGBColor area_light_shade(ShadeRec& sr);

    //virtual RGBColor path_shade(ShadeRec& sr);

    //virtual RGBColor global_shade(ShadeRec& sr);

private:
    PerfectSpecular* reflective_brdf;
    PerfectTransmitter* specular_btdf;
};

inline void Transparent::setKr(const float k) {
    reflective_brdf->setKr(k);
}

inline void Transparent::setCr(const RGBColor& c) {
    reflective_brdf->setCr(c);
	
}

inline void Transparent::setCr(const float r, const float g, const float b) {
    reflective_brdf->setCr(r, g, b);
}

inline void Transparent::setCr(const float c) {
    reflective_brdf->setCr(c);
}

inline void Transparent::setIor(const float eta){
    specular_btdf->setIor(eta);
}

inline void Transparent::setKt(const float k){
    specular_btdf->setKt(k);
}
#endif
