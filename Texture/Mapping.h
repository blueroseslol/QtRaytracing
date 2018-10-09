#ifndef __MAPPING__
#define __MAPPING__

#include <math.h>

#include "Utilities/Point3D.h"

class Mapping {		
	public:
        Mapping();

        ~Mapping();
				
        virtual void getTexelCoordinates(	const 	Point3D& 	hit_point,
								const 	int 		xres, 
								const 	int 		yres, 
										int& 		row, 
										int& 		column) const = 0;
};
#endif
