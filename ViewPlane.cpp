#include "ViewPlane.h"

ViewPlane::ViewPlane()
{

}

void ViewPlane::set_hres(int _hres)
{
    hres=_hres;
}

void ViewPlane::set_vres(int _vres)
{
    vres=_vres;
}

void ViewPlane::set_pixel_size(float _pixel_size)
{
    s=_pixel_size;
}

void ViewPlane::set_gamma(float _gamma)
{
    gamma=_gamma;
}

int hres;
int vres;
float s;
float gamma;
float inv_gamma;


