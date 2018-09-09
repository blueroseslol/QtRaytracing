#ifndef __MATERIAL__
#define __MATERIAL__

#include "World.h"
#include "Utilities/RGBColor.h"
#include "Utilities/ShadeRec.h"

class Material {	
public:
        Material();
		
		Material(const Material& material); 

        Material(Material&& material);
		
//        virtual Material*	clone(void) const = 0;
				
        virtual ~Material();
				
        virtual RGBColor shade(ShadeRec& sr);

        virtual RGBColor areaLightShade(ShadeRec& sr);
protected:
        Material& operator= (const Material& rhs);
};

#endif

