#include "WrappedFBmTexture.h"

WrappedFBmTexture::WrappedFBmTexture(LatticeNoise* texture)
: Texture(), noise_ptr(texture), color(1.0f, 1.0f, 1.0f), min_value(0.0f), max_value(1.0f),
expansion_number(1.0)
{

}

WrappedFBmTexture::WrappedFBmTexture(const WrappedFBmTexture& texture)
: Texture(texture), noise_ptr(texture.noise_ptr), color(texture.color), min_value(texture.min_value),
max_value(texture.max_value), expansion_number(texture.expansion_number)
{

}

WrappedFBmTexture::WrappedFBmTexture(WrappedFBmTexture &&texture)
:Texture(texture), noise_ptr(texture.noise_ptr), color(texture.color), min_value(texture.min_value),
max_value(texture.max_value), expansion_number(texture.expansion_number)
{

}

WrappedFBmTexture::~WrappedFBmTexture(){
}

RGBColor WrappedFBmTexture::getColor(const ShadeRec& sr) const {

	float noise = expansion_number * noise_ptr->value_fbm(sr.local_hit_point);
	float value = noise - floor(noise);
	value = min_value + (max_value - min_value) * value;

	return (value * color);
}
