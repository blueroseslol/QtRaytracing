#ifndef __TURBULENCE_TEXTURE__
#define __TURBULENCE_TEXTURE__

#include "Texture.h"
#include "Utilities/Constants.h"
#include "LatticeNoise.h"

class TurbulenceTexture : public Texture {
public:

	// constructors etc ...
	TurbulenceTexture(LatticeNoise* texture);

	TurbulenceTexture(const TurbulenceTexture& texture);

    TurbulenceTexture(TurbulenceTexture&& texture);

    ~TurbulenceTexture();

	TurbulenceTexture& operator= (const TurbulenceTexture& rhs);

    virtual RGBColor getColor(const ShadeRec& sr) const;

    void setColor(float r, float g, float b);

    void setMinValue(float min);

    void setMaxValue(float max);
private:
	LatticeNoise*		noise_ptr;
	RGBColor 	  		color;
	float		  		min_value, max_value;	// scaling factors
};


inline void TurbulenceTexture::setColor(float r, float g, float b){
	color = RGBColor(r, g, b);
}

inline void TurbulenceTexture::setMinValue(float min){
	min_value = min;
}

inline void TurbulenceTexture::setMaxValue(float max){
	max_value = max;
}
#endif
