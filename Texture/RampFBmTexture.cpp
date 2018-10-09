#include "RampFBmTexture.h"

RampFBmTexture::RampFBmTexture(Image* image)
: Texture(), ramp_ptr(image), noise_ptr(nullptr), perturbation(1.0f)
{

}

RampFBmTexture::RampFBmTexture(const RampFBmTexture& texture)
: Texture(texture), ramp_ptr(texture.ramp_ptr), noise_ptr(texture.noise_ptr),
perturbation(texture.perturbation)
{

}

RGBColor RampFBmTexture::getColor(const ShadeRec& sr) const {

	float 	noise = noise_ptr->value_fbm(sr.local_hit_point);
	float 	y = sr.local_hit_point.y + perturbation * noise;
	float 	u = (1.0 + sin(y)) / 2.0;
	int 	row = 0;    // use top row of ramp image
    int 	column = (int)(u * (ramp_ptr->getHres() - 1));

    return (ramp_ptr->getColor(row, column));
}
