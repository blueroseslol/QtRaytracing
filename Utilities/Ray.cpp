// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Ray.h"

// ---------------------------------------------------------------- default constructor

Ray::Ray ()
    : 	origin(0.0),
        direction(0.0, 0.0, 1.0)
{}

// ---------------------------------------------------------------- constructor

Ray::Ray (const Point3D& origin, const Vector3D& direction)
    : 	origin(origin),
        direction(direction)
{}

// ---------------------------------------------------------------- copy constructor

Ray::Ray (const Ray& ray)
    : 	origin(ray.origin),
        direction(ray.direction)
{}

Ray::Ray (Ray&& ray)
    : 	origin(ray.origin),
        direction(ray.direction)
{}
// ---------------------------------------------------------------- assignment operator

Ray& 
Ray::operator= (const Ray& rhs) {
	
	if (this == &rhs)
		return (*this);
		
    origin = rhs.origin;
    direction = rhs.direction;

	return (*this);	
}

Ray&
Ray::operator= (Ray&& rhs) {

    if (this == &rhs)
        return (*this);

    origin = rhs.origin;
    direction = rhs.direction;

    return (*this);
}
// ---------------------------------------------------------------- destructor

Ray::~Ray () {}




