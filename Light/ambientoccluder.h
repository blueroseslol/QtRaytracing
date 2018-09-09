#ifndef AMBIENTOCCLUDER_H
#define AMBIENTOCCLUDER_H
#include "Light/light.h"
#include "Sampler/sampler.h"
class AmbientOccluder : public Light
{
public:
    AmbientOccluder();

//    AmbientOccluder(const AmbientOccluder& ao);

//    AmbientOccluder(AmbientOccluder&& ao);

    ~AmbientOccluder();

    void setSampler(Sampler* s_ptr);

    virtual Vector3D getDirection(ShadeRec &sr);

    virtual bool inShadow(const Ray &ray, const ShadeRec &sr) const;

    virtual RGBColor L(ShadeRec &sr);

    void scaleRadiance(const float& radiance);

    void setColor(const RGBColor& _color);

    void setMinAmount(const float& min);
private:
    Vector3D u,v,w;
    Sampler* sampler_ptr;
    RGBColor min_amount;
    float ls;
    RGBColor color;
};

#endif // AMBIENTOCCLUDER_H
