#include "fisheye.h"
#include <math.h>
#include "Utilities/Constants.h"
FishEye::FishEye():Camera(),rSquared(1)
{

}

Ray FishEye::getRay(Point2D &point) const
{
    //TODO:存在问题，以后修正
    float s=1;
    Point2D pn(2.0/(s*hres)*point.x,2.0/(s*vres)*point.y);
    int rSquared=(int)(pn.x*pn.x+pn.y*pn.y);

    if(rSquared<=1.0){
        double r=sqrt(rSquared);
        double psi=r*psiMax*PI_ON_180;
        double sin_psi=sin(psi);
        double cos_psi=cos(psi);
        double sin_alpha=pn.x/r;
        double cos_alpha=pn.y/r;
        Vector3D dir(sin_psi*cos_alpha*u+sin_psi*sin_alpha*v-cos_psi*w);
        return Ray(origin,dir);
    }else
        return Ray(origin,Vector3D(0.0));
}
