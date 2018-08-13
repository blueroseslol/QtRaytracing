#include "normalmaterial.h"
#include <QDebug>
NormalMaterial::NormalMaterial():Material()
{

}

RGBColor NormalMaterial::shade(ShadeRec& sr) {
    return RGBColor(0.5*(sr.normal.x+1),0.5*(sr.normal.y+1),1.0);
}
