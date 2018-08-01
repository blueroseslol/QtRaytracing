#ifndef WORLD_H
#define WORLD_H
#include "Utilities/RGBColor.h"
#include "Geometry/Geometry.h"
#include "Cameras/Camera.h"
#include <QImage>
#include <QObject>
#include <QColor>
#include "rendersetting.h"
#include <QVector>
#include <QImage>
class Tracer;
class World : public QObject
{
    Q_OBJECT
public:
    World();
    World(RenderSetting *_setting);

    RenderSetting* setting;
    QImage *image;
    float progress;

    ~World();

    void addGeometry(Geometry *geometryPtr);

    ShadeRec hit_bare_bones_objects(const Ray& ray) const;

    void build();

    void render_scene();

    inline void setCamera(Camera *cameraPtr);
private:
    Camera* camera_ptr;
    Tracer* tracer_ptr;
    QVector<Geometry*> scene;
signals:
    void renderComplete();
};

inline void World::setCamera(Camera *cameraPtr)
{
    camera_ptr=cameraPtr;
}

#endif // WORLD_H
