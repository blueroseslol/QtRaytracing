// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Matte.h"
#include <QDebug>
// ---------------------------------------------------------------- default constructor

Matte::Matte ():Material(),
		ambient_brdf(new Lambertian),
		diffuse_brdf(new Lambertian)
{}



// ---------------------------------------------------------------- copy constructor

Matte::Matte(const Matte& m): Material(m),
    ambient_brdf(new std::remove_pointer<decltype(m.ambient_brdf)>::type (*m.ambient_brdf)),
    diffuse_brdf(new std::remove_pointer<decltype(m.diffuse_brdf)>::type (*m.diffuse_brdf))
{
//	if(m.ambient_brdf)
//		ambient_brdf = m.ambient_brdf->clone();
//	else  ambient_brdf = NULL;
	
//	if(m.diffuse_brdf)
//		diffuse_brdf = m.diffuse_brdf->clone();
    //	else  diffuse_brdf = NULL;
}

Matte::Matte(Matte &&m): Material(m),ambient_brdf(m.ambient_brdf),diffuse_brdf(m.diffuse_brdf)
{
    m.ambient_brdf=nullptr;
    m.diffuse_brdf=nullptr;
}


// ---------------------------------------------------------------- clone

//Material* Matte::clone(void) const {
//	return (new Matte(*this));
//}


// ---------------------------------------------------------------- assignment operator

//Matte& Matte::operator= (const Matte& rhs) {
//	if (this == &rhs)
//		return (*this);
		
//	Material::operator=(rhs);
	
//	if (ambient_brdf) {
//		delete ambient_brdf;
//		ambient_brdf = NULL;
//	}

//	if (rhs.ambient_brdf)
//		ambient_brdf = rhs.ambient_brdf->clone();
		
//	if (diffuse_brdf) {
//		delete diffuse_brdf;
//		diffuse_brdf = NULL;
//	}

//	if (rhs.diffuse_brdf)
//		diffuse_brdf = rhs.diffuse_brdf->clone();

//	return (*this);
//}


// ---------------------------------------------------------------- destructor

Matte::~Matte() {

	if (ambient_brdf) {
		delete ambient_brdf;
        ambient_brdf = nullptr;
	}
	
	if (diffuse_brdf) {
		delete diffuse_brdf;
        diffuse_brdf = nullptr;
	}
}


// ---------------------------------------------------------------- shade

RGBColor Matte::shade(ShadeRec& sr) {
    Vector3D 	wo 			= -sr.ray.direction;
    RGBColor 	L 			= ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
    for (int j = 0; j < sr.w.lights.length(); j++) {
        Vector3D wi = sr.w.lights[j]->getDirection(sr);
        float ndotwi = sr.normal * wi;
	
        if (ndotwi > 0.0){
            bool inShadow=false;
            if(sr.w.lights[j]->castShadow){
                Ray shadowRay(sr.hit_point,wi);
                inShadow=sr.w.lights[j]->inShadow(shadowRay,sr);
            }
            if(!inShadow){
                L += diffuse_brdf->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * ndotwi;
            }
        }
    }
	
    return L;
}

RGBColor Matte::areaLightShade(ShadeRec& sr){
    Vector3D wo=-sr.ray.direction;
    RGBColor L=ambient_brdf->rho(sr,wo)*sr.w.ambient_ptr->L(sr);

    for(int j=0;j<sr.w.lights.length();j++){
        Vector3D wi=sr.w.lights[j]->getDirection(sr);
        float ndotwi=sr.normal.wi;

        if(ndotwi>0.0){
            bool inShadow=false;

            if(sr.w.lights[j]->castShadow){
                Ray shadowRay(sr.hit_point,wi);
                inShadow=sr.w.lights[j]->inShadow(shadowRay,sr);
            }
            if(!inShadow){
                L=+diffuse_brdf->f(sr,wo,wi)*sr.w.lights[j]->L(sr)*sr.w.lights[j]->G(sr)*ndotwi/sr.w.lights[j]->pdf(sr);
            }
        }
    }
}
