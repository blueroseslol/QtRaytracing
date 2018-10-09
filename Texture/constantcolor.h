#ifndef CONSTANTCOLOR_H
#define CONSTANTCOLOR_H
#include "Texture.h"

class ConstantColor : public Texture
{
public:
    ConstantColor();

    virtual RGBColor getColor(const ShadeRec &sr) const override;

    RGBColor setColor(const RGBColor& c);
private:
    RGBColor color;
};

inline RGBColor ConstantColor::getColor(const ShadeRec &sr) const
{
    return color;
}

inline RGBColor ConstantColor::setColor(const RGBColor &c)
{
    color=c;
}

#endif // CONSTANTCOLOR_H
