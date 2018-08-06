#include "Camera.h"
#include "Utilities/Maths.h"
Camera::Camera():origin(0,0,100),lookat(0),up(0,1,0),u(1,0,0),v(0, 1, 0),
    w(0, 0, 1),
    exposureTime(1.0)
{
//    lower_left_corner = origin - half_width*u*focus_dist - half_height*v*focus_dist - focus_dist*w;
//    horizontal = 2 * half_width*u*focus_dist;
//    vertical = 2*half_height*v*focus_dist;
}

void Camera::computeUVW()
{
    w=origin-lookat;
    w.normalize();
    // cross product
    u=up^w;
    u.normalize();
    v=w^u;
}
