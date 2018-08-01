#ifndef CAMERA_H
#define CAMERA_H
#include "Utilities/Point3D.h"
#include "Utilities/Vector3D.h"
#include "Utilities/Ray.h"
class World;
class Camera
{
public:
    Camera();
    void computeUVW();

    virtual void renderScene(World* world)=0;

    Ray getRay(double u,double v) const;

    inline void setOrigin(const Point3D& p);

    inline void setOrigin(const float x, const float y, const float z);

    inline void setLookat(const Point3D& p);

    inline void setLookat(const float x, const float y, const float z);

    inline void setUpVector(const Vector3D& u);

    inline void setUpVector(const float x, const float y, const float z);

    inline void setExposureTime(const float _exposureTime);

    inline void setRollAngle(const float& angle);

//    virtual Vector3D getDirection(const Point2D& uv) const;
protected:
    Point3D origin;
    Point3D lookat;
    Vector3D up;
    Vector3D u,v,w;

    Vector3D lower_left_corner;
    Vector3D horizontal;
    Vector3D vertical;
    float exposureTime;
};

inline void Camera::setOrigin(const Point3D &p)
{
    origin=p;
}

inline void Camera::setOrigin(const float x, const float y, const float z)
{
    origin=Point3D(x,y,z);
}


inline void Camera::setLookat(const Point3D &p)
{
    lookat=p;
}

inline void Camera::setLookat(const float x, const float y, const float z)
{
    lookat=Point3D(x,y,z);
}

inline void Camera::setUpVector(const Vector3D &u)
{
    up=u;
}

inline void Camera::setUpVector(const float x, const float y, const float z)
{
    up=Vector3D(x,y,z);
}

inline void Camera::setExposureTime(const float _exposureTime)
{
    exposureTime=_exposureTime;
}

//TODO:实现倾斜角
void Camera::setRollAngle(const float &angle)
{

}

#endif // CAMERA_H
