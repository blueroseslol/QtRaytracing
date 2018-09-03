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
    return sp.x*u+sp.y*v+sp.z*w;
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
    w=sr.normal;
    v=w^Vector3D(0.0072,1.0,0.0034);
    v.normalize();
    u=v^w;

    Ray shadowRay;
    shadowRay.origin=sr.hit_point;
    shadowRay.direction=getDirection(sr);

    if(inShadow(shadowRay,sr))
        return min_amount*ls*color;
    else
        return ls*color;
}
