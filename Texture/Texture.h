#ifndef __TEXTURE__
#define __TEXTURE__

#include <math.h>
#include "Utilities/ShadeRec.h"
#include "Utilities/RGBColor.h"

class Texture {	
	public:
        Texture();

        Texture(const Texture& texture);

        Texture(Texture&& texture);

        ~Texture();
		
        virtual RGBColor	 getColor(const ShadeRec& sr) const = 0;
};

#endif
		
