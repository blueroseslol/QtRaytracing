#ifndef __FRESNEL_TRANSMITTER__
#define __FRESNEL_TRANSMITTER__

#include "BTDF.h"

class FresnelTransmitter : public BTDF {
public:

    FresnelTransmitter();

	FresnelTransmitter(const FresnelTransmitter& pt);

    FresnelTransmitter(FresnelTransmitter&& pt);

    ~FresnelTransmitter();

	bool tir(const ShadeRec& sr) const;

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

    virtual RGBColor sampleF(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;

	float fresnel(const ShadeRec& sr) const;

    void setEtaIn(float value);

    void setEtaOut(float value);

private:
	float eta_in;
	float eta_out;
};

inline void FresnelTransmitter::setEtaIn(float value){
	eta_in = value;
}

inline void FresnelTransmitter::setEtaOut(float value){
	eta_out = value;
}
#endif
