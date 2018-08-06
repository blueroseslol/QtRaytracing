#ifndef PINHOLE_H
#define PINHOLE_H
#include "Cameras/Camera.h"

class Pinhole : public Camera
{
public:
    Pinhole();

//    Vector3D rayDirction(Point2D& point) const;

    virtual Ray getRay(Point2D &point) const override;

    inline void setViewDistance(const float& _distance);
private:
    //view-plane distance
    float distance;
    float zoom;
};

inline void Pinhole::setViewDistance(const float &_distance)
{
    distance=_distance;
}

#endif // PINHOLE_H
