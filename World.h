#ifndef WORLD_H
#define WORLD_H
#include "Utilities/RGBColor.h"
#include "Geometry/Geometry.h"
#include "Cameras/Camera.h"
#include "Light/ambient.h"
#include "Light/ambientoccluder.h"
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
    QVector<Geometry*> scene;
    QVector<Material*> material;
    QVector<Light*> lights;
//    Ambient* ambient_ptr;
    AmbientOccluder* ambient_ptr;
    Tracer* tracer_ptr;
    Sampler* sampler_ptr;
    float progress;
    bool terminate;

    ~World();

    void addGeometry(Geometry *geometryPtr);

    ShadeRec hit_bare_bones_objects(const Ray& ray) const;

    ShadeRec hitObject(const Ray& ray) const;

    void build();

    void render_scene();

    QColor postProcess(int& u, int &v, RGBColor &pixelColor);

    inline void setCamera(Camera *cameraPtr);

    void clearScene();

    void addLight(Light *lightPtr);
private:
    Camera* camera_ptr;

    Tracer* areaLightTracer_ptr;
signals:
    void renderComplete();
};

inline void World::setCamera(Camera *cameraPtr)
{
    camera_ptr=cameraPtr;
}

#endif // WORLD_H
