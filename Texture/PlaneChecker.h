#ifndef __PLANE_CHECKER__
#define __PLANE_CHECKER__

#include "Texture.h"

class PlaneChecker : public Texture{
public:
    PlaneChecker();

	PlaneChecker(const PlaneChecker& texture);

    PlaneChecker(PlaneChecker&& it);

    ~PlaneChecker();

    virtual RGBColor getColor(const ShadeRec& sr) const;

    void setSize(const float value);

    void setOutlineWidth(const float value);

    void setColor1(RGBColor color);

    void setColor2(RGBColor color);

    void setOutlineColor(RGBColor color);
protected:
	float size;
	float outline_width;
	RGBColor color1, color2, outline_color;
};

inline void PlaneChecker::setSize(const float value){
	size = value;
}

inline void PlaneChecker::setOutlineWidth(const float value){
	outline_width = value;
}

inline void PlaneChecker::setColor1(RGBColor color){
	color1 = color;
}

inline void PlaneChecker::setColor2(RGBColor color){
	color2 = color;
}

inline void PlaneChecker::setOutlineColor(RGBColor color){
	outline_color = color;
}
#endif
