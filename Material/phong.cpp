#include "phong.h"

Phong::Phong():Material()
  ,ambient_brdf(new Lambertian),diffuse_brdf(new Lambertian),specular_brdf(new GlossySpecular)
{

}

Phong::Phong(const Phong &phong):Material(phong)
  ,ambient_brdf(new std::remove_pointer<decltype(phong.ambient_brdf)>::type (*phong.ambient_brdf)),
    diffuse_brdf(new std::remove_pointer<decltype(phong.diffuse_brdf)>::type (*phong.diffuse_brdf)),
    specular_brdf(new std::remove_pointer<decltype(phong.specular_brdf)>::type (*phong.specular_brdf))
{

}

Phong::Phong(Phong &&phong):Material(phong),ambient_brdf(phong.ambient_brdf),diffuse_brdf(phong.diffuse_brdf),
specular_brdf(phong.specular_brdf)
{
    phong.ambient_brdf=nullptr;
    phong.diffuse_brdf=nullptr;
    phong.specular_brdf=nullptr;
}

Phong::~Phong()
{
    if (ambient_brdf) {
        delete ambient_brdf;
        ambient_brdf = nullptr;
    }

    if (diffuse_brdf) {
        delete diffuse_brdf;
        diffuse_brdf = nullptr;
    }

    if(specular_brdf){
        delete specular_brdf;
        specular_brdf=nullptr;
    }
}

RGBColor Phong::shade(ShadeRec &sr)
{
    Vector3D wo=-sr.ray.direction;
    RGBColor L=ambient_brdf->rho(sr,wo)*sr.w.ambient_ptr->L(sr);
    int num_lights	= sr.w.lights.size();
    for(int j=0;j<num_lights;j++){
        Vector3D wi=sr.w.lights[j]->getDirection(sr);
        float ndotwi=sr.normal*wi;
        if(ndotwi>0.0){
            L+=(diffuse_brdf->f(sr,wo,wi)+specular_brdf->f(sr,wo,wi))*sr.w.lights[j]->L(sr)*ndotwi;
        }
    }
    return L;
}
