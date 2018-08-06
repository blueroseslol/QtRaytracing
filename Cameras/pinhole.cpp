#include "pinhole.h"

Pinhole::Pinhole():Camera(),distance(200),zoom(1.0)
{

}

//Vector3D Pinhole::rayDirction(Point2D &point) const
//{
//    Vector3D dir = point.x * u + point.y * v - distance * w;
//    dir.normalize();

//    return(dir);
//}

Ray Pinhole::getRay(Point2D& point) const
{
    Vector3D dir = point.x * u + point.y * v - distance * w;
    dir.normalize();
    return Ray(origin,dir);
}
