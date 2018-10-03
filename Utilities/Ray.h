#ifndef __RAY__
#define __RAY__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Point3D.h"
#include "Vector3D.h"

class Ray {
	public:
	
        Point3D			origin;  	// origin
        Vector3D		direction; 		// direction
		
        Ray();
		
        Ray(const Point3D& origin, const Vector3D& direction);
		
		Ray(const Ray& ray); 		
        Ray(Ray&& ray);

        Ray& operator= (const Ray& rhs);

        Ray& operator= (Ray&& rhs);

        ~Ray();
};

#endif

