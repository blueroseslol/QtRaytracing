#ifndef NORMALMATERIAL_H
#define NORMALMATERIAL_H
#include "Material/material.h"

class NormalMaterial : public Material
{
public:
    NormalMaterial();
    virtual RGBColor shade(ShadeRec &sr);
};

#endif // NORMALMATERIAL_H
