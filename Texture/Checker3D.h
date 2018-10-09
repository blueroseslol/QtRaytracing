#ifndef __CHECKER_3D__
#define __CHECKER_3D__

#include "Texture.h"

class Checker3D : public Texture
{
public:
    Checker3D();

	Checker3D(const Checker3D& texture);

    Checker3D(Checker3D&& it);

    ~Checker3D();

    virtual RGBColor getColor(const ShadeRec& sr) const;

    void setSize(const float value);

    void setColor1(RGBColor color);
    void setColor2(RGBColor color);

protected:
	float size;
	RGBColor color1, color2;
};

inline void Checker3D::setSize(const float value){
	size = value;
}

inline void Checker3D::setColor1(RGBColor color){
	color1 = color;
}

inline void Checker3D::setColor2(RGBColor color){
	color2 = color;
}

#endif
