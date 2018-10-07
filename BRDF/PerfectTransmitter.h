#ifndef __PERFECT_TRANSMITTER__
#define __PERFECT_TRANSMITTER__

#include "BTDF.h"

class PerfectTransmitter: public BTDF {
public:
    PerfectTransmitter();

    PerfectTransmitter(const PerfectTransmitter& pt);

    PerfectTransmitter(PerfectTransmitter&& pt);

    ~PerfectTransmitter();

    void setKt(const float k);

    void setIor(const float eta);

    bool tir(const ShadeRec& sr) const;

    virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

    virtual RGBColor sampleF(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const;

    virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;
private:
    float kt;		// transmission coefficient
    float ior;		// index of refraction
};

inline void PerfectTransmitter::setKt(const float k) {
	kt = k;
}

inline void PerfectTransmitter::setIor(const float eta) {
	ior = eta;
}
#endif
