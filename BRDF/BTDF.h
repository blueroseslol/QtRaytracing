#ifndef __BTDF__
#define __BTDF__

#include <math.h>

#include "Utilities/Constants.h"
#include "Utilities/Vector3D.h"
#include "Utilities/ShadeRec.h"

class BTDF {
public:
    BTDF();

    BTDF(const BTDF& btdf);

    BTDF(BTDF&& btdf);

    ~BTDF();

    virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;

    virtual RGBColor sampleF(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt) const;

    virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;

    virtual bool tir(const ShadeRec& sr) const;
};
#endif
