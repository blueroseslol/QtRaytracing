#include "Camera.h"
#include "Utilities/Maths.h"
Camera::Camera():origin(0,0,100),lookat(0),up(0,1,0),u(1,0,0),v(0, 1, 0),
    w(0, 0, 1),
    exposureTime(1.0)
{
    lower_left_corner = origin - half_width*u*focus_dist - half_height*v*focus_dist - focus_dist*w;
    horizontal = 2 * half_width*u*focus_dist;
    vertical = 2*half_height*v*focus_dist;
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

Ray Camera::getRay(double u, double v) const
{
    vec3 rd = lens_radius*random_in_unit_disk();
    vec3 offset = u*rd.x(); +v*rd.y();
    double time = time0 + uni_dist(reng)*(time1 - time0);
    return Ray(origin+offset, lower_left_corner + s*horizontal + t*vertical - origin-offset);
}

//Vector3D Camera::getDirection(const Point2D &uv) const
//{

//}
