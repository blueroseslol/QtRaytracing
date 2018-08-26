#ifndef PHONG_H
#define PHONG_H
#include "Material/material.h"

class Phong
{
public:
    Phong();

    Phong(const Phong& phong);

    Phong(Phong&& phong);

    virtual RGBColor shade(ShadeRec& sr);
};

#endif // PHONG_H
