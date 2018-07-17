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

    void set_hres(int hres);
    void set_vres(int vres);
    void set_pixel_size(float pixel_size);
    void set_gamma(float gamma);
};

#endif // VIEWPLANE_H
