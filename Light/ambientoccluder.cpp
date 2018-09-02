#include "ambientoccluder.h"
#include "World.h"
AmbientOccluder::AmbientOccluder():Light(),sampler_ptr(nullptr)
{

}

void AmbientOccluder::setSampler(Sampler *s_ptr)
{
    if(sampler_ptr){
        delete sampler_ptr;
        sampler_ptr=nullptr;
    }
    sampler_ptr=s_ptr;
    sampler_ptr->map_samples_to_hemisphere(1);
}

Vector3D AmbientOccluder::getDirection(ShadeRec &sr)
{
    Point3D sp=sampler_ptr->sampleHemisphere();
    return sp.x*u+
}

bool AmbientOccluder::inShadow(const Ray &ray, const ShadeRec &sr) const
{
    float t;
    for(int j=0;j<sr.w.scene.length();j++){
        if(sr.w.scene[j]->shadowHit(ray,t))
            return true;
    }
    return false;
}

RGBColor AmbientOccluder::L(ShadeRec &sr)
{

}
