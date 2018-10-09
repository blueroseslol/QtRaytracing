﻿#include "PlaneChecker.h"

PlaneChecker::PlaneChecker()
: Texture(), size(1.0f), outline_width(0.1f), color1(1.0f,1.0f,1.0f),
color2(1.0f, 1.0f, 1.0f), outline_color(1.0f, 1.0f, 1.0f)
{

}

PlaneChecker::PlaneChecker(const PlaneChecker& it)
: Texture(it), size(it.size), outline_width(it.outline_width),color1(it.color1),
color2(it.color2), outline_color(it.outline_color)

{
}

PlaneChecker::PlaneChecker(PlaneChecker &&it)
: Texture(it), size(it.size), outline_width(it.outline_width),color1(it.color1),
color2(it.color2), outline_color(it.outline_color)
{

}

PlaneChecker::~PlaneChecker(){
}

RGBColor PlaneChecker::getColor(const ShadeRec& sr) const {

	float x = sr.local_hit_point.x;
	float z = sr.local_hit_point.z;
	int ix = floor(x / size);
	int iz = floor(z / size);
	float fx = x / size - ix;
	float fz = z / size - iz;
	float width = 0.5f * outline_width / size;
	bool in_outline = (fx < width || fx > 1.0 - width) || (fz < width || fz > 1.0 - width);

	if ((ix + iz) % 2 == 0) {
		if (!in_outline)
			return (color1);
	}
	else {
		if (!in_outline)
			return (color2);
	}

	return (outline_color);
}
