// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Ray.h"

// ---------------------------------------------------------------- default constructor

Ray::Ray (void)
    : 	origin(0.0),
		d(0.0, 0.0, 1.0) 
{}

// ---------------------------------------------------------------- constructor

Ray::Ray (const Point3D& origin, const Vector3D& direction)
    : 	origin(origin),
        d(direction)
{}

// ---------------------------------------------------------------- copy constructor

Ray::Ray (const Ray& ray)
    : 	origin(ray.o),
		d(ray.d) 
{}

Ray::Ray (Ray&& ray)
    : 	origin(ray.o),
        d(ray.d)
{}
// ---------------------------------------------------------------- assignment operator

Ray& 
Ray::operator= (const Ray& rhs) {
	
	if (this == &rhs)
		return (*this);
		
    origin = rhs.origin;
	d = rhs.d; 

	return (*this);	
}

Ray&
Ray::operator= (Ray&& rhs) {

    if (this == &rhs)
        return (*this);

    origin = rhs.origin;
    d = rhs.d;

    return (*this);
}
// ---------------------------------------------------------------- destructor

Ray::~Ray (void) {}




