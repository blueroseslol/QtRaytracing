#ifndef __WRAPPED_FBM_TEXTURE__
#define __WRAPPED_FBM_TEXTURE__

#include "Texture.h"
#include "Utilities/Constants.h"
#include "LatticeNoise.h"

class WrappedFBmTexture : public Texture {
public:
	WrappedFBmTexture(LatticeNoise* texture);

	WrappedFBmTexture(const WrappedFBmTexture& texture);

    WrappedFBmTexture(WrappedFBmTexture&& texture);

    ~WrappedFBmTexture();

    virtual RGBColor getColor(const ShadeRec& sr) const;

    void setColor(float r, float g, float b);

    void setMinValue(float min);

    void setMaxValue(float max);

    void setExpansionNumber(float value);
private:
	LatticeNoise*		noise_ptr;
	RGBColor 	  		color;
	float		  		min_value, max_value;	// scaling factors
	float expansion_number;
};

inline void WrappedFBmTexture::setColor(float r, float g, float b){
	color = RGBColor(r, g, b);
}

inline void WrappedFBmTexture::setMinValue(float min){
	min_value = min;
}

inline void WrappedFBmTexture::setMaxValue(float max){
	max_value = max;
}

inline void WrappedFBmTexture::setExpansionNumber(float value){
	expansion_number = value;
}
#endif
