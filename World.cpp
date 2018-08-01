#include "World.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <QDebug>
#include <QtConcurrent>
#include <QFutureSynchronizer>
//#include "Tracer/singlesphere.h"
#include "Tracer/mutipleobjects.h"
#include "Utilities/Point2D.h"
//#include "Sampler/jittered.h"
//#include "Sampler/regular.h"
#include "Sampler/multijittered.h"
#include "Sampler/hammersley.h"
#include "Cameras/pinhole.h"
#include "Geometry/sphere.h"

#include "tbb/tbb.h"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range2d.h"
World::World(RenderSetting *_setting):setting(_setting),tracer_ptr(nullptr),image(nullptr),progress(0.0)
{
}

World::~World(){
    if(tracer_ptr)
        delete tracer_ptr;
    if(image)
        delete image;
}

void World::build(){
    //TODO:这里应该使用智能指针
    tracer_ptr=new MutipleObjects(this);
    Sphere *sphere=new Sphere(Point3D(0.0,0.0,-1),0.5);
    sphere->setColor(RGBColor(1.0,0,0));
    addGeometry(sphere);

    Sphere *sphere1=new Sphere(Point3D(0.2,0.2,-0.8),0.3);
    sphere1->setColor(RGBColor(0,1.0,0));
    addGeometry(sphere1);

//    setting->setSampler(new Jittered(16,3));
//    setting->setSampler(new Regular(16));
    setting->setSampler(new MultiJittered(16,3));
//    setting->setSampler(new Hammersley(16,3));

    Pinhole* pinhole=new Pinhole;
    pinhole->setOrigin(300,400,500);
    pinhole->setLookat(0,0,-50);
    pinhole->setViewDistance(400);
    pinhole->computeUVW();
    setCamera(pinhole);
}

void World::addGeometry(Geometry *geometryPtr){
    scene.push_back(geometryPtr);
}

//TODO:个人认为这个东西还是放到MutilObject Tracer里比较好
ShadeRec World::hit_bare_bones_objects(const Ray &ray) const
{
    ShadeRec sr(*this);
    double t;
    double tmin=DBL_MAX;
    for(auto it=scene.begin();it!=scene.end();it++){
        if((*it)->hit(ray,t,sr)&&(t<tmin)){
           sr.hit_an_object=true;
           tmin=t;
           sr.color=(*it)->getColor();
        }
    }
    return sr;
}

void World::render_scene() {
    if(image)
        delete image;
    image=new QImage(setting->imageWidth,setting->imageHeight,QImage::Format_RGB888);

    QtConcurrent::run([this](){
    //    int nthreads = tbb::task_scheduler_init::automatic;
    //    tbb::task_scheduler_init init (nthreads-1);
    Point2D sp;//采样点坐标
    Point2D pp;//pixel上的采样点
    int nx = setting->imageWidth;
    int ny =  setting->imageHeight;
    int allPixelNum=nx*ny;
    int currentPixelNum=0;

    Vector3D lower_left_corner(-2.0, -1.0, -1.0);
    Vector3D horizontal(4.0, 0.0, 0.0);
    Vector3D vertical(0.0, 2.0, 0.0);
    Point3D origin(0.0, 0.0, 0.0);

    tbb::spin_mutex mutex;
    tbb::parallel_for( tbb::blocked_range2d<int>(0, nx, 1, 0, ny, 1),
                       [&](const tbb::blocked_range2d<int>& r)
    {
        for( int i=r.rows().begin(); i!=r.rows().end(); ++i ){
            for( int j=r.cols().begin(); j!=r.cols().end(); ++j ) {
                RGBColor pixelColor;
                Ray ray;
                ray.origin=origin;
//                ray.origin=camera_ptr->getOrigin();
                for(int k=0;k<setting->numSamples;k++){
                    sp=setting->samplerPtr->sampleUnitSquare();
                    float u = float(i+sp.x) / float(nx);
                    float v = float(j+sp.y) / float(ny);

                    ray.direction=lower_left_corner+u*horizontal+v*vertical;

                    pixelColor+= tracer_ptr->trace_ray(ray);
                }
                mutex.lock();
                pixelColor/=setting->numSamples;
                image->setPixelColor(i,j,QColor( int(255.99*pixelColor.r), int(255.99*pixelColor.g), int(255.99*pixelColor.b)));
                currentPixelNum++;
                progress=currentPixelNum*100/allPixelNum;
                mutex.unlock();
            }
        }
    });
    emit renderComplete();});
}
