#ifndef WORLD_H
#define WORLD_H
#include "Utilities/RGBColor.h"
#include "Geometry/sphere.h"
//#include "Cameras/Camera.h"
#include <QImage>
#include <QObject>
#include <QColor>
#include "rendersetting.h"
class Tracer;
class World : public QObject
{
    Q_OBJECT
public:
    //Camera camera;
    Sphere sphere;
    Tracer* tracer_ptr;
    RenderSetting* setting;

    World();
    World(RenderSetting *_setting);
    ~World();

    void build();

    void render_scene();

signals:
    void pixelComplete(int u,int v,int progress,QColor color);
    void renderComplete();
};

#endif // WORLD_H
