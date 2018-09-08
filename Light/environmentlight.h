#ifndef ENVIRONMENTLIGHT_H
#define ENVIRONMENTLIGHT_H
#include "Light/light.h"
#include "Sampler/sampler.h"
class EnvironmentLight : public Light
{
public:
    EnvironmentLight();

    EnvironmentLight(const EnvironmentLight& el);

    EnvironmentLight(EnvironmentLight&& el);

    void setSampler();

    virtual Vector3D getDirection(ShadeRec &sr);

    virtual RGBColor L(ShadeRec &sr);

    bool inShadow(const Ray &ray, const ShadeRec &sr) const;

    virtual float pdf(const ShadeRec& sr) const;
private:
    Sampler* sampler_ptr;
    Material* material_ptr;
    Vector3D u,v,w;
    Vector3D wi;
};

#endif // ENVIRONMENTLIGHT_H
