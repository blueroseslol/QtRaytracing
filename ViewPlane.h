﻿#ifndef VIEWPLANE_H
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
};

#endif // VIEWPLANE_H
