#ifndef __LIGHT__
#define __LIGHT__

#include "Utilities/Vector3D.h"
#include "Utilities/RGBColor.h"
#include "Utilities/Ray.h"
#include "Utilities/ShadeRec.h"

class Light {	
public:

    Light();

    Light(const Light& ls);

    Light(Light&& ls);

    Light& operator= (const Light& rhs);

    virtual ~Light();

    virtual Vector3D	getDirection(ShadeRec& sr) = 0;

    virtual RGBColor	 L(ShadeRec& sr);

    virtual bool inShadow(const Ray& ray,const ShadeRec& sr) const;

    virtual float G(const ShadeRec& sr) const;

    virtual float pdf(const ShadeRec& sr) const;
    bool castShadow;
};

#endif
