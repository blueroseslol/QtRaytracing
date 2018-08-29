#include "Light.h"
#include "Utilities/Constants.h"

Light::Light():castShadow(true) {}

Light::Light(const Light& ls):castShadow(ls.castShadow) {}

Light::Light(Light &&ls):castShadow(ls.castShadow){}

Light& Light::operator= (const Light& rhs) {
	if (this == &rhs)
		return (*this);
	return (*this);
}

Light::~Light() {}

RGBColor Light::L(ShadeRec& s) {
    return RGBColor();
}

bool Light::inShadow(const Ray &ray, const ShadeRec &sr) const
{
    return false;
}
