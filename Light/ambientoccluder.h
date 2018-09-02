#ifndef AMBIENTOCCLUDER_H
#define AMBIENTOCCLUDER_H
#include "Light/light.h"
#include "Sampler/sampler.h"
class AmbientOccluder : public Light
{
public:
    AmbientOccluder();

    void setSampler(Sampler* s_ptr);

    virtual Vector3D getDirection(ShadeRec &sr);

    virtual bool inShadow(const Ray &ray, const ShadeRec &sr) const;

    virtual RGBColor L(ShadeRec &sr);
private:
    Vector3D u,v,w;
    Sampler* sampler_ptr;
    RGBColor min_amount;
};

#endif // AMBIENTOCCLUDER_H
