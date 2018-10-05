﻿#ifndef __WHITTED__
#define __WHITTED__
#include "Tracer.h"

class Whitted: public Tracer {
public:

    Whitted();

    Whitted(World* _worldPtr);

    ~Whitted();

    virtual RGBColor trace_ray(const Ray& ray, const int depth) const override;
};

#endif
