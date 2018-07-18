#ifndef VIEWPLANE_H
#define VIEWPLANE_H


class ViewPlane
{
public:
    ViewPlane();

    int hres;
    int vres;
    float s;
    float gamma;
    float inv_gamma;

    void set_hres(int _hres);
    void set_vres(int _vres);
    void set_pixel_size(float _pixel_size);
    void set_gamma(float _gamma);
};

#endif // VIEWPLANE_H
