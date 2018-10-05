#ifndef __GLOSSYREFLECTIVE__
#define __GLOSSYREFLECTIVE__

#include "Phong.h"

class GlossyReflector : public Phong {
public:
    GlossyReflector();

    GlossyReflector(const GlossyReflector& rm);

    GlossyReflector(GlossyReflector&& rm);

    ~GlossyReflector();

    void setSamples(const int num_samples, const float exp);

    void setKr(const float k);

    void setCr(const RGBColor& c);

    void setCr(const float r, const float g, const float b);

    void setExponent(const float exp);

    virtual RGBColor shade(ShadeRec &sr);

    virtual RGBColor areaLightShade(ShadeRec& sr);

private:

    GlossySpecular* glossy_specular_brdf;
};

inline void
GlossyReflector::setSamples(const int num_samples, const float exp) {
    glossy_specular_brdf->setSamples(num_samples, exp);
}

inline void
GlossyReflector::setKr(const float k) {
    glossy_specular_brdf->setKs(k);
}

inline void GlossyReflector::setCr(const RGBColor& c) {
    glossy_specular_brdf->setCs(c);
}

inline void
GlossyReflector::setExponent(const float exp) {
    glossy_specular_brdf->setExp(exp);
}

inline void GlossyReflector::setCr(const float r, const float g, const float b){
    glossy_specular_brdf->setCs(r, g, b);
}

#endif
