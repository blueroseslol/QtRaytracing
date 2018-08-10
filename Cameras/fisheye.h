#ifndef FISHEYE_H
#define FISHEYE_H
#include "Cameras/Camera.h"

class FishEye : public Camera
{
public:
    FishEye();

    virtual Ray getRay(Point2D &point) const override;

    inline void setResoultion(const int _hres,const int _vres);

    inline void setPsiMax(const float _psiMax);

    inline float getRSquared() const;
private:
    float psiMax;
    int hres;
    int vres;
    int rSquared;
};

inline void FishEye::setResoultion(const int _hres, const int _vres)
{
    hres=_hres;
    vres=_vres;
}

inline void FishEye::setPsiMax(const float _psiMax)
{
    psiMax=_psiMax;
}

inline float FishEye::getRSquared() const
{
    return (float)rSquared;
}

#endif // FISHEYE_H
