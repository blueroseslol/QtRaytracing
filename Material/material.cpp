// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Material.h"

// ---------------------------------------------------------------- default constructor

Material::Material() {}


// ---------------------------------------------------------------- copy constructor

Material::Material(const Material& m) {}

Material::Material(Material&& material){}


// ---------------------------------------------------------------- assignment operator

Material& Material::operator= (const Material& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}


// ---------------------------------------------------------------- destructor

Material::~Material()
{}


// ---------------------------------------------------------------- shade

RGBColor Material::shade(ShadeRec& sr) {
    return RGBColor();
}

RGBColor Material::areaLightShade(ShadeRec &sr)
{
    return RGBColor(0);
}




