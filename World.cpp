#include "World.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <QDebug>
#include <QtConcurrent>
#include <QFutureSynchronizer>
#include <QScopedPointer>

#include "Utilities/Constants.h"
#include "Utilities/Point2D.h"

//#include "Tracer/singlesphere.h"
//#include "Tracer/mutipleobjects.h"
#include "Tracer/raycast.h"

//#include "Sampler/jittered.h"
#include "Sampler/regular.h"
#include "Sampler/multijittered.h"
#include "Sampler/hammersley.h"

#include "Cameras/pinhole.h"
//#include "Cameras/fisheye.h"

#include "Light/directional.h"
#include "Light/pointlight.h"

#include "Geometry/sphere.h"
#include "Geometry/plane.h"
#include "Material/Matte.h"
#include "Material/phong.h"

#include "tbb/tbb.h"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range2d.h"
World::World(RenderSetting *_setting):setting(_setting),tracer_ptr(nullptr),image(nullptr),progress(0.0),terminate(false),
    ambient_ptr(nullptr)
{
}

World::~World(){
    if(image)
        delete image;
}

void World::build(){
    tracer_ptr=new RayCast(this);
    sampler_ptr=new MultiJittered(1,1);
//    ambient_ptr=new Ambient;
//    ambient_ptr->scaleRadiance(2.0);
//    ambient_ptr->setColor(0.3,0.3,0.3);
    ambient_ptr=new AmbientOccluder();
    ambient_ptr->scaleRadiance(1.0);
    ambient_ptr->setColor(RGBColor(1.0));
    ambient_ptr->setMinAmount(0.0);
    ambient_ptr->setSampler(new Regular(1));

//    Directional* light_ptr=new Directional;
//    light_ptr->setDirection(1,0.0,1);
//    light_ptr->scaleRadiance(1.0);
//    light_ptr->setColor(2,2,2);
//    addLight(light_ptr);

//    PointLight* pointLight_ptr=new PointLight;
//    pointLight_ptr->setLocation(4,4,3);
//    pointLight_ptr->setColor(3,3,3);
//    addLight(pointLight_ptr);

    Matte *matte_ptr=new Matte;
    matte_ptr->setKa(0.25);
    matte_ptr->setKd(0.65);
    matte_ptr->setCd(RGBColor(1.0,1.0,1.0));
    material.push_back(matte_ptr);

    Matte *matte2_ptr=new Matte;
    matte2_ptr->setKa(0.25);
    matte2_ptr->setKd(0.65);
    matte2_ptr->setCd(RGBColor(1.0,1.0,1.0));
    material.push_back(matte2_ptr);

    Phong* phong_ptr=new Phong;
    phong_ptr->setKa(0.25);
    phong_ptr->setKd(0.6);
    phong_ptr->setCd(RGBColor(0.5));
    phong_ptr->setSpecularKs(0.75);
    phong_ptr->setSpecularExp(20);
    material.push_back(phong_ptr);


    Plane *plane=new Plane(Point3D(0,-1,0),Normal(0,1,0));
    plane->setMaterial(matte2_ptr);
    addGeometry(plane);

    Sphere *sphere=new Sphere(Point3D(0.0,0.0,-1),1);
    sphere->setMaterial(matte_ptr);
    addGeometry(sphere);

    Sphere *sphere1=new Sphere(Point3D(1,1,1),0.5);
    sphere1->setMaterial(phong_ptr);
    addGeometry(sphere1);

    setting->setSampler(sampler_ptr);

    Pinhole* pinhole=new Pinhole;
    pinhole->setOrigin(0,0,8);
    pinhole->setLookat(0,0,0);
    pinhole->setViewDistance(1000);
    pinhole->computeUVW();
    setCamera(pinhole);

}
void World::addLight(Light *lightPtr){
    lights.push_back(lightPtr);
}

void World::addGeometry(Geometry *geometryPtr){
    scene.push_back(geometryPtr);
}

void World::clearScene(){
    for (auto it = scene.begin(); it != scene.end(); it++) {
        delete (*it);
    }
    scene.clear();

    for (auto it = material.begin(); it != material.end(); it++) {
        delete (*it);
    }
    material.clear();

    for (auto it = lights.begin(); it != lights.end(); it++) {
        delete (*it);
    }
    lights.clear();
    if(ambient_ptr){
        delete ambient_ptr;
        ambient_ptr=nullptr;
    }
    if(tracer_ptr){
        delete tracer_ptr;
        tracer_ptr=nullptr;
    }
    if(sampler_ptr){
        delete sampler_ptr;
        sampler_ptr=nullptr;
    }

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
    terminate=false;

    QtConcurrent::run([this](){
//        int nthreads = tbb::task_scheduler_init::automatic;
//        tbb::task_scheduler_init init;
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
                if(terminate){
                    tbb::task::self().cancel_group_execution();
                }
                RGBColor pixelColor;
                Point2D sp;//采样点坐标
                Point2D pp;//pixel上的采样点
                for(int k=0;k<setting->numSamples;k++){
                    sp=setting->samplerPtr->sampleUnitSquare();
/*
    本书的坐标映射方式有问题
*/
                    pp.x=i-0.5*nx+sp.x;
                    pp.y=j-0.5*ny+sp.y;

                    pixelColor+= tracer_ptr->trace_ray(camera_ptr->getRay(pp),0);
                }
                mutex.lock();
                pixelColor/=setting->numSamples;
                pixelColor*=camera_ptr->getExposureTime();
                //对j进行翻转操作
                int jReversal=ny-j-1;
                image->setPixelColor(i,jReversal,postProcess(i,jReversal,pixelColor));
                currentPixelNum++;
                progress=currentPixelNum*100/allPixelNum;
                mutex.unlock();
            }
        }
    });
    emit renderComplete();
    clearScene();
    });
}

QColor World::postProcess(int &u, int &v,RGBColor& pixelColor)
{
    if(pixelColor.r>1 && pixelColor.g>1 && pixelColor.b>1)
    {
        return QColor(255,255,255);
    }
    float maxValue=max(pixelColor.r,max(pixelColor.g,pixelColor.b));
    if(maxValue>1)
    {
        pixelColor/=maxValue;
    }

    return QColor( int(255.99*pixelColor.r), int(255.99*pixelColor.g), int(255.99*pixelColor.b));
}
