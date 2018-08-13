// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Light.h"

#include "Utilities/Constants.h"

// ---------------------------------------------------------------------- default constructor

Light::Light() {}

// ---------------------------------------------------------------------- copy constructor

Light::Light(const Light& ls) {}


// ---------------------------------------------------------------------- assignment operator

Light& 
Light::operator= (const Light& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}


// ---------------------------------------------------------------------- destructor

Light::~Light() {}



// ---------------------------------------------------------------------- L
// returns the radiance

RGBColor								
Light::L(ShadeRec& s) {
    return RGBColor();
}



