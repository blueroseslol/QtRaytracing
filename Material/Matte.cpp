// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Matte.h"
#include <QDebug>
#include "Tracer/tracer.h"
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

RGBColor Matte::shade(ShadeRec& sr) {
    Vector3D wo= -sr.ray.direction;
    RGBColor L= ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
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
        float ndotwi=sr.normal*wi;

        if(ndotwi>0.0){
            bool inShadow=false;

            if(sr.w.lights[j]->castShadow){
                Ray shadowRay(sr.hit_point,wi);
                inShadow=sr.w.lights[j]->inShadow(shadowRay,sr);
            }
            if(!inShadow){
                L+=diffuse_brdf->f(sr,wo,wi)*sr.w.lights[j]->L(sr)*sr.w.lights[j]->G(sr)*ndotwi/sr.w.lights[j]->pdf(sr);
            }
        }
    }
    return L;
}

RGBColor Matte::pathShade(ShadeRec &sr)
{
//	qDebug() << "!";
    Vector3D wi;
    Vector3D wo=-sr.ray.direction;
    float pdf;
    RGBColor f=diffuse_brdf->sampleF(sr,wo,wi,pdf);
    Ray reflectedRay(sr.hit_point,wi);
	RGBColor color = sr.w.tracer_ptr->trace_ray(reflectedRay, sr.depth + 1);
    return f*color*(sr.normal*wi)/pdf;
}

RGBColor Matte::globalShade(ShadeRec &sr)
{
    RGBColor L;
    if(sr.depth==0)
        L=areaLightShade(sr);
    Vector3D wi;
    Vector3D wo=-sr.ray.direction;
    float pdf;
    RGBColor f=diffuse_brdf->sampleF(sr,wo,wi,pdf);
    float ndotwi=sr.normal*wi;
    Ray reflectedRay(sr.hit_point,wi);

    L+=f*sr.w.tracer_ptr->trace_ray(reflectedRay,sr.depth+1)*ndotwi/pdf;
    return L;
}

void Matte::setSamples(const int numSamples, const float exp)
{
	diffuse_brdf->setSamples(numSamples);
}
