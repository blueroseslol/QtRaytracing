#ifndef __REFLECTIVE__
#define __REFLECTIVE__

#include "Material/Phong.h"
#include "BRDF/PerfectSpecular.h"

class Reflective: public Phong {	
public:
    Reflective();

    Reflective(const Reflective& rm);

    Reflective(Reflective&& rm);

    ~Reflective();

    void setKr(const float k);

    void setCr(const RGBColor& c);

    void setCr(const float r, const float g, const float b);

    void setCr(const float c);

    virtual RGBColor shade(ShadeRec& s);
private:

    PerfectSpecular* reflective_brdf;
};

inline void Reflective::setKr(const float k) {
    reflective_brdf->setKr(k);
}

inline void Reflective::setCr(const RGBColor& c) {
    reflective_brdf->setCr(c);

}

inline void Reflective::setCr(const float r, const float g, const float b) {
    reflective_brdf->setCr(r, g, b);
}

inline void Reflective::setCr(const float c) {
    reflective_brdf->setCr(c);
}

#endif
