#ifndef WORLD_H
#define WORLD_H
#include "Utilities//RGBColor.h"
#include "Geometry/sphere.h"
#include "Tracer.h"
#include "Cameras/Camera.h"

class World
{
public:
    Camera camera;
    RGBColor background_color;
    Sphere sphere;
    Tracer* tracer_ptr;

    World();

    void build();

    void render_scene() const;
};

#endif // WORLD_H
