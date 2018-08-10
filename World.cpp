#include "World.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <QDebug>
#include <QtConcurrent>
#include <QFutureSynchronizer>

#include "Utilities/Constants.h"
#include "Utilities/Point2D.h"

//#include "Tracer/singlesphere.h"
//#include "Tracer/mutipleobjects.h"
#include "Tracer/raycast.h"


//#include "Sampler/jittered.h"
//#include "Sampler/regular.h"
#include "Sampler/multijittered.h"
#include "Sampler/hammersley.h"

#include "Cameras/pinhole.h"
#include "Cameras/fisheye.h"

#include "Geometry/sphere.h"
#include "Material/normalmaterial.h"

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
    NormalMaterial *mat=new NormalMaterial();

//    tracer_ptr=new MutipleObjects(this);
    tracer_ptr=new RayCast(this);
    Sphere *sphere=new Sphere(Point3D(0.0,0.0,-1),0.5);
    sphere->setMaterial(mat);
//    sphere->setColor(RGBColor(1.0,0,0));
    addGeometry(sphere);

//    Sphere *sphere1=new Sphere(Point3D(0.2,0.2,-0.8),0.3);
////    sphere1->setColor(RGBColor(0,1.0,0));
//    sphere1->setMaterial(mat);
//    addGeometry(sphere1);

//    setting->setSampler(new Jittered(16,3));
//    setting->setSampler(new Regular(16));
    setting->setSampler(new MultiJittered(16,3));
//    setting->setSampler(new Hammersley(16,3));

    Pinhole* pinhole=new Pinhole;
    pinhole->setOrigin(0,0,5);
    pinhole->setLookat(0,0,0);
    pinhole->setViewDistance(1000);
    pinhole->computeUVW();
    setCamera(pinhole);

//    FishEye* fishEye=new FishEye;
//    fishEye->setOrigin(0,0,2);
//    fishEye->setLookat(0,0,0);
//    fishEye->computeUVW();
//    fishEye->setResoultion(setting->imageWidth,setting->imageHeight);
//    fishEye->setPsiMax(270);
//    setCamera(fishEye);
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

ShadeRec World::hitObject(const Ray &ray) const
{
    ShadeRec sr(*this);
    double t;
    Normal normal;
    Point3D local_hit_point;
    double tmin=DBL_MAX;

    for(auto it=scene.begin();it!=scene.end();it++){

        if((*it)->hit(ray,t,sr)&&(t<tmin)){
           sr.hit_an_object=true;
           tmin=t;
            sr.material_ptr=(*it)->getMaterial();
            sr.hit_point=ray.origin+t*ray.direction;
            normal=sr.normal;
            local_hit_point=sr.local_hit_point;
        }
        if(sr.hit_an_object){
            sr.t=tmin;
            sr.normal=normal;
            sr.local_hit_point=local_hit_point;
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
    int nx = setting->imageWidth;
    int ny =  setting->imageHeight;
    int allPixelNum=nx*ny;
    int currentPixelNum=0;

    tbb::spin_mutex mutex;
    tbb::parallel_for( tbb::blocked_range2d<int>(0, nx, 1, 0, ny, 1),
                       [&](const tbb::blocked_range2d<int>& r)
    {
        for( int i=r.rows().begin(); i!=r.rows().end(); ++i ){
            for( int j=r.cols().begin(); j!=r.cols().end(); ++j ) {
                RGBColor pixelColor;
                Point2D sp;//采样点坐标
                Point2D pp;//pixel上的采样点
                for(int k=0;k<setting->numSamples;k++){
                    sp=setting->samplerPtr->sampleUnitSquare();
                    pp.x=i-0.5*nx+sp.x;
                    pp.y=j-0.5*ny+sp.y;

                    pixelColor+= tracer_ptr->trace_ray(camera_ptr->getRay(pp),0);
                }
                mutex.lock();
                pixelColor/=setting->numSamples;
                pixelColor*=camera_ptr->getExposureTime();
                image->setPixelColor(i,j,QColor( int(255.99*pixelColor.r), int(255.99*pixelColor.g), int(255.99*pixelColor.b)));
                currentPixelNum++;
                progress=currentPixelNum*100/allPixelNum;
                mutex.unlock();
            }
        }
    });
    emit renderComplete();});
}
