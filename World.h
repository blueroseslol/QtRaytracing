#ifndef WORLD_H
#define WORLD_H
#include "Utilities/RGBColor.h"
#include "Geometry/sphere.h"
//#include "Cameras/Camera.h"
#include <QImage>
#include <QObject>
#include <QColor>
#include "rendersetting.h"
#include <QVector>
class Tracer;
class World : public QObject
{
    Q_OBJECT
public:
    //Camera camera;
    Tracer* tracer_ptr;
    RenderSetting* setting;
    QVector<Geometry*> scene;

    World();
    World(RenderSetting *_setting);
    ~World();

    void addGeometry(Geometry *geometryPtr);

    ShadeRec hit_bare_bones_objects(const Ray& ray) const;

    void build();

    void render_scene();

signals:
    void pixelComplete(int u,int v,float progress,QColor color);
    void renderComplete();
};

#endif // WORLD_H
