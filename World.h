#ifndef WORLD_H
#define WORLD_H
#include "Utilities/RGBColor.h"
#include "Geometry/sphere.h"
//#include "Cameras/Camera.h"
#include "ViewPlane.h"
#include <QImage>
#include <QFutureSynchronizer>
#include <QObject>
#include <QColor>
class Tracer;
class World : public QObject
{
    Q_OBJECT
public:
    //Camera camera;
    RGBColor background_color;
    Sphere sphere;
    Tracer* tracer_ptr;
    ViewPlane vp;
    World();

    void build();

    void render_scene();

signals:
    void pixelComplete(int u,int v,QColor color);
};

#endif // WORLD_H
