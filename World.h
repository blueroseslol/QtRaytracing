#ifndef WORLD_H
#define WORLD_H
#include "Utilities/RGBColor.h"
#include "Geometry/sphere.h"
#include "Cameras/Camera.h"
#include "ViewPlane.h"
#include <QImage>

class Tracer;
class World
{
public:
    Camera camera;
    RGBColor background_color;
    Sphere sphere;
    Tracer* tracer_ptr;
    ViewPlane vp;
    World();

    QImage *image;

    void build();

    QImage *render_scene();
};

#endif // WORLD_H
