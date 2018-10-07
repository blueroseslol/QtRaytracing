#ifndef __DIELECTRIC__
#define __DIELECTRIC__

#include "Phong.h"
#include "BRDF/FresnelReflector.h"
#include "BRDF/FresnelTransmitter.h"

class Dielectric : public Phong {
public:
    Dielectric();

    Dielectric(const Dielectric& rm);

    Dielectric(Dielectric&& rm);

    ~Dielectric();

    virtual RGBColor shade(ShadeRec& s);

    void setIor(const float eta);

    void setEtaIn(float value);

    void setEtaOut(float value);

    void setCfIn(RGBColor color);

    void setCfIn(float r, float g, float b);

    void setCfOut(RGBColor color);

    void setCfOut(float r, float g, float b);

private:
    RGBColor 			cf_in;			// interior filter color
    RGBColor 			cf_out;			// exterior filter color

    FresnelReflector*	fresnel_reflector_brdf;
    FresnelTransmitter*	fresnel_transmitter_btdf;
};

inline void Dielectric::setCfIn(RGBColor color){
	cf_in = color;
}

inline void Dielectric::setCfOut(RGBColor color){
	cf_out = color;
}

inline void Dielectric::setCfIn(float r, float g, float b){
	cf_in.r = r;
	cf_in.g = g;
	cf_in.b = b;
}

inline void Dielectric::setCfOut(float r, float g, float b){
	cf_out.r = r;
	cf_out.g = g;
	cf_out.b = b;
}
#endif
