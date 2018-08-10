#include "normalmaterial.h"
#include <QDebug>
NormalMaterial::NormalMaterial():Material()
{

}

RGBColor NormalMaterial::shade(ShadeRec& sr) {
    return RGBColor(sr.normal.x,sr.normal.y,sr.normal.z);
}
