﻿// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Directional.h"

// ---------------------------------------------------------------------- default constructor

Directional::Directional()
	: 	Light(),
		ls(1.0),
		color(1.0),
		dir(0, 1, 0)			
{}


// ---------------------------------------------------------------------- dopy constructor

Directional::Directional(const Directional& dl)
	: 	Light(dl),
		ls(dl.ls),
		color(dl.color),
		dir(dl.dir)  		
{}

Directional::Directional(Directional&& dl)
    : 	Light(dl),
        ls(dl.ls),
        color(dl.color),
        dir(dl.dir)
{}
// ---------------------------------------------------------------------- clone

//Light*
//Directional::clone(void) const {
//	return (new Directional(*this));
//}


// ---------------------------------------------------------------------- assignment operator

//Directional&
//Directional::operator= (const Directional& rhs)
//{
//	if (this == &rhs)
//		return (*this);
			
//	Light::operator= (rhs);
	
//	ls		= rhs.ls;
//	color 	= rhs.color;
//	dir 	= rhs.dir;

//	return (*this);
//}


// ---------------------------------------------------------------------- destructor																			

Directional::~Directional() {}


// ---------------------------------------------------------------------- get_direction
// as this function is virtual, it shouldn't be inlined 

Vector3D								
Directional::getDirection(ShadeRec& sr) {
	return (dir);
}	

// ------------------------------------------------------------------------------  L

RGBColor
Directional::L(ShadeRec& s) {	
    return (ls * color);
}

bool Directional::inShadow(const Ray &ray, const ShadeRec &sr) const
{
    double t;
    for(int j=0;j<sr.w.scene.length();j++){
        if(sr.w.scene[j]->shadowHit(ray,t))
        return true;
    }
    return false;
}



