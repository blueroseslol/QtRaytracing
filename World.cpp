#include "World.h"
//#define _USE_MATH_DEFINES
#include <math.h>
#include <QDebug>
#include <QtConcurrent>

#include "Utilities/Constants.h"
#include "Utilities/Point2D.h"

#include "Tracer/raycast.h"
#include "Tracer/arealighting.h"
#include "Tracer/whitted.h"
#include "Tracer/pathtrace.h"
#include "Tracer/globeltracer.h"

#include "Sampler/regular.h"
#include "Sampler/multijittered.h"
#include "Sampler/hammersley.h"

#include "Cameras/pinhole.h"

#include "Light/directional.h"
#include "Light/pointlight.h"
#include "Light/arealight.h"
#include "Light/environmentlight.h"

#include "Geometry/sphere.h"
#include "Geometry/plane.h"
#include "Geometry/rectangular.h"
#include "Geometry/box.h"
#include "Geometry/Triangles/Triangle.h"
#include "Geometry/Instance.h"
#include "Geometry/compound.h"
#include "Geometry/grid.h"
#include "Material/Matte.h"
#include "Material/phong.h"
#include "Material/emissive.h"
#include "Material/Reflective.h"
#include "Material/GlossyReflector.h"
#include "Material/Transparent.h"

#include "tbb/tbb.h"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range2d.h"

World::World(RenderSetting *_setting):setting(_setting),tracer_ptr(nullptr),areaLightTracer_ptr(nullptr),image(nullptr),progress(0.0),terminate(false),
    ambient_ptr(nullptr)
{

}

World::~World(){
    if(image)
        delete image;
}

void World::build(){
//    cornellBox();
    //tracer_ptr=new RayCast(this);
    tracer_ptr=new Whitted(this);
    setting->maxDepth=10;
    sampler_ptr=new MultiJittered(256,3);
//    ambient_ptr=new Ambient;
//    ambient_ptr->scaleRadiance(2.0);
//    ambient_ptr->setColor(0.3,0.3,0.3);
    ambient_ptr=new AmbientOccluder();
    ambient_ptr->scaleRadiance(1.0);
    ambient_ptr->setColor(RGBColor(1.0));
    ambient_ptr->setMinAmount(0.0);
//    ambient_ptr->setSampler(new MultiJittered(64,3));
    ambient_ptr->setSampler(sampler_ptr);

    Directional* light_ptr=new Directional;
    light_ptr->setDirection(1,0.0,1);
    light_ptr->scaleRadiance(1.0);
    light_ptr->setColor(2,2,2);
    addLight(light_ptr);

    PointLight* pointLight_ptr=new PointLight;
    pointLight_ptr->setLocation(4,4,3);
    pointLight_ptr->setColor(3,3,3);
    addLight(pointLight_ptr);

    Emissive* emissive_env_ptr=new Emissive;
    emissive_env_ptr->scaleRadiance(1.0);
    emissive_env_ptr->setCe(1.0,1.0,0.5);
    material.push_back(emissive_env_ptr);

    EnvironmentLight* envLight_ptr=new EnvironmentLight;
    envLight_ptr->setMaterial(emissive_env_ptr);
    envLight_ptr->setSampler(sampler_ptr);
    envLight_ptr->castShadow=true;
    addLight(envLight_ptr);
//面光源
//---------------------------------------------------------------------------
//    Emissive* emissive_ptr=new Emissive;
////        emissive_ptr->scaleRadiance(20.0);
//    emissive_ptr->scaleRadiance(20);
//    emissive_ptr->setCe(1.0,1.0,1.0);
//    material.push_back(emissive_ptr);

//    Point3D p0=Point3D(0,2,0);
//    Vector3D a=Vector3D(0,0,1);
//    Vector3D b=Vector3D(1,0,0);

//    Rectangular* rectangle_ptr=new Rectangular(p0,a,b,Normal(0,-1,0));
//    rectangle_ptr->setMaterial(emissive_ptr);
//    rectangle_ptr->setSampler(sampler_ptr);
//    rectangle_ptr->castShadow=false;
//    addGeometry(rectangle_ptr);

//    areaLightTracer_ptr=new AreaLighting(this);

//    AreaLight* areaLight_ptr=new AreaLight;
//    areaLight_ptr->setObject(rectangle_ptr);
//    areaLight_ptr->castShadow=true;
//    addLight(areaLight_ptr);
//---------------------------------------------------------------------------
    Matte *matte_ptr=new Matte;
    matte_ptr->setKa(0.25f);
    matte_ptr->setKd(0.65f);
    matte_ptr->setCd(RGBColor(1.0,1.0,1.0));
    matte_ptr->setSamples(16, 1);
    material.push_back(matte_ptr);

    Matte *matte2_ptr=new Matte;
    matte2_ptr->setKa(0.25f);
    matte2_ptr->setKd(0.65f);
    matte2_ptr->setCd(RGBColor(1.0,1.0,1.0));
    material.push_back(matte2_ptr);

    Phong* phong_ptr=new Phong;
    phong_ptr->setKa(0.25f);
    phong_ptr->setKd(0.6f);
    phong_ptr->setCd(RGBColor(0.5));
    phong_ptr->setSpecularKs(0.75);
    phong_ptr->setSpecularExp(20);
    material.push_back(phong_ptr);

    Reflective* reflection_ptr=new Reflective;
    reflection_ptr->setKa(0.25f);
    reflection_ptr->setKd(0.5f);
    reflection_ptr->setCd(RGBColor(0.75,0.75,0));
    reflection_ptr->setSpecularKs(0.15);
    reflection_ptr->setSpecularExp(100);
    reflection_ptr->setKr(0.75);
    reflection_ptr->setCr(RGBColor(1.0));
    material.push_back(reflection_ptr);

    GlossyReflector *glossy_ptr=new GlossyReflector;
    glossy_ptr->setKa(0.25f);
    glossy_ptr->setKd(0.5f);
    glossy_ptr->setCd(RGBColor(0,0.75,0.75));
    glossy_ptr->setSpecularKs(0.15);
    glossy_ptr->setSpecularExp(100);
    glossy_ptr->setKr(0.75);
    glossy_ptr->setCr(RGBColor(1.0));
    glossy_ptr->setSamples(16,20);
    material.push_back(glossy_ptr);

    Transparent* glass_ptr=new Transparent;
    glass_ptr->setKr(0.5);
    glass_ptr->setIor(1.5);
    glass_ptr->setKr(0.1);
    glass_ptr->setKt(0.9);


    Triangle *triangle=new Triangle(Point3D(0,-0.5,0),Point3D(0,0,1),Point3D(1,0,0));
    triangle->setMaterial(matte_ptr);
//    addGeometry(triangle);
    Plane *plane=new Plane(Point3D(0,-1,0),Normal(0,1,0));
    plane->setMaterial(matte_ptr);
    addGeometry(plane);

    Sphere *sphere=new Sphere(Point3D(0.0,0.0,-1),1);
    sphere->setMaterial(glass_ptr);
//    addGeometry(sphere);

    Instance *instance=new Instance(sphere);
    instance->setMaterial(matte_ptr);
    instance->translate(-1,2,-1);
    instance->scale(1,0.5,0.5);
    instance->computeBoundingBox();
//    addGeometry(instance);

    Grid *grid_ptr = new Grid;
    grid_ptr->addObject(instance);
    grid_ptr->addObject(sphere);
    grid_ptr->addObject(triangle);
    grid_ptr->setupCells();
    addGeometry(grid_ptr);

//    Sphere *sphere1=new Sphere(Point3D(1,1,1),0.5);
//    sphere1->setMaterial(phong_ptr);
//    addGeometry(sphere1);

//    Box* box=new Box(Point3D(-2,0,-2),Point3D(-1,1,-1));
//    box->setMaterial(matte_ptr);
//    addGeometry(box);

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

void World::cornellBox()
{
    int num_samples =256;
    tracer_ptr=new GlobelTracer(this);
//    tracer_ptr = new PathTrace(this);
    setting->maxDepth=10;
    sampler_ptr=new MultiJittered(num_samples,3);
    setting->setSampler(sampler_ptr);
        ambient_ptr=new AmbientOccluder();
        ambient_ptr->scaleRadiance(1.0);
        ambient_ptr->setColor(RGBColor(1.0));
        ambient_ptr->setMinAmount(0.0);
        ambient_ptr->setSampler(sampler_ptr);

    Pinhole* pinhole=new Pinhole;
    pinhole->setOrigin(27.6,27.4, -80.0);
    pinhole->setLookat(27.6,27.4, 0.0);
    pinhole->setViewDistance(400);
    pinhole->computeUVW();
    setCamera(pinhole);

    setting->imageWidth=300;
    setting->imageHeight=300;

    Point3D p0;
    Vector3D a, b;
    Normal normal;

    // box dimensions

    double width = 55.28;        // x direction
    double height          = 54.88;          //y direction
    double depth = 55.92;   //z direction


    // the ceiling light -doesn't need samples

    Emissive* emissive_ptr= new Emissive;
    emissive_ptr->setCe(1.0,0.73, 0.4);
    emissive_ptr->scaleRadiance(100);

    p0 = Point3D(21.3,height - 0.001, 22.7);
    a = Vector3D(0.0, 0.0,10.5);
    b = Vector3D(13.0, 0.0,0.0);
    normal = Normal(0.0,-1.0, 0.0);
    Rectangular* light_ptr =new Rectangular(p0, a, b, normal);
    light_ptr->setMaterial(emissive_ptr);
    addGeometry(light_ptr);


    // left wall

    Matte* matte_ptr1 =new Matte;
    matte_ptr1->setKa(0.0);
    matte_ptr1->setKd(0.6);
    matte_ptr1->setCd(0.57,0.025, 0.025);       // red
    matte_ptr1->setSamples(num_samples,1);

    p0 = Point3D(width,0.0, 0.0);
    a = Vector3D(0.0, 0.0,depth);
    b = Vector3D(0.0,height, 0.0);
    normal = Normal(-1.0,0.0, 0.0);
    Rectangular*left_wall_ptr = new Rectangular(p0, a, b, normal);
    left_wall_ptr->setMaterial(matte_ptr1);
    addGeometry(left_wall_ptr);


    // right wall

    Matte* matte_ptr2 =new Matte;
    matte_ptr2->setKa(0.0);
    matte_ptr2->setKd(0.6);
    matte_ptr2->setCd(0.37,0.59, 0.2);     // green   from Photoshop
    matte_ptr2->setSamples(num_samples,1);

    p0 = Point3D(0.0, 0.0,0.0);
    a = Vector3D(0.0, 0.0,depth);
    b = Vector3D(0.0,height, 0.0);
    normal = Normal(1.0,0.0, 0.0);
    Rectangular*right_wall_ptr = new Rectangular(p0, a, b, normal);
    right_wall_ptr->setMaterial(matte_ptr2);
    addGeometry(right_wall_ptr);


    // back wall

    Matte* matte_ptr3 =new Matte;
    matte_ptr3->setKa(0.0);
    matte_ptr3->setKd(0.6);
    matte_ptr3->setCd(1.0);        // white
    matte_ptr3->setSamples(num_samples,1);

    p0 = Point3D(0.0, 0.0,depth);
    a = Vector3D(width,0.0, 0.0);
    b = Vector3D(0.0,height, 0.0);
    normal = Normal(0.0,0.0, -1.0);
    Rectangular*back_wall_ptr = new Rectangular(p0, a, b, normal);
    back_wall_ptr->setMaterial(matte_ptr3);
    addGeometry(back_wall_ptr);


    // floor

    p0 = Point3D(0.0, 0.0,0.0);
    a = Vector3D(0.0, 0.0,depth);
    b = Vector3D(width,0.0, 0.0);
    normal = Normal(0.0,1.0, 0.0);
    Rectangular* floor_ptr =new Rectangular(p0, a, b, normal);
    floor_ptr->setMaterial(matte_ptr3);
    addGeometry(floor_ptr);


    // ceiling

    p0 = Point3D(0.0,height, 0.0);
    a = Vector3D(0.0, 0.0,depth);
    b = Vector3D(width,0.0, 0.0);
    normal = Normal(0.0,-1.0, 0.0);
    Rectangular* ceiling_ptr= new Rectangular(p0, a, b, normal);
    ceiling_ptr->setMaterial(matte_ptr3);
    addGeometry(ceiling_ptr);
    // top

    p0 = Point3D(13.0,16.5, 6.5);
    a = Vector3D(-4.8,0.0, 16.0);
    b = Vector3D(16.0,0.0, 4.9);
    normal = Normal(0.0,1.0, 0.0);
    Rectangular*short_top_ptr = new Rectangular(p0, a, b, normal);
    short_top_ptr->setMaterial(matte_ptr3);
    addGeometry(short_top_ptr);


    // side 1

    p0 = Point3D(13.0,0.0, 6.5);
    a = Vector3D(-4.8,0.0, 16.0);
    b = Vector3D(0.0,16.5, 0.0);
    Rectangular*short_side_ptr1 = new Rectangular(p0, a, b);
    short_side_ptr1->setMaterial(matte_ptr3);
    addGeometry(short_side_ptr1);


    // side 2

    p0 = Point3D(8.2, 0.0,22.5);
    a = Vector3D(15.8,0.0, 4.7);
    Rectangular*short_side_ptr2 = new Rectangular(p0, a, b);
    short_side_ptr2->setMaterial(matte_ptr3);
    addGeometry(short_side_ptr2);


    // side 3

    p0 = Point3D(24.2,0.0, 27.4);
    a = Vector3D(4.8, 0.0,-16.0);
    Rectangular* short_side_ptr3= new Rectangular(p0, a, b);
    short_side_ptr3->setMaterial(matte_ptr3);
    addGeometry(short_side_ptr3);


    // side 4

    p0 = Point3D(29.0,0.0, 11.4);
    a = Vector3D(-16.0,0.0, -4.9);
    Rectangular*short_side_ptr4 = new Rectangular(p0, a, b);
    short_side_ptr4->setMaterial(matte_ptr3);
    addGeometry(short_side_ptr4);




    // tall box

    // top

    p0 = Point3D(42.3,33.0, 24.7);
    a = Vector3D(-15.8,0.0, 4.9);
    b = Vector3D(4.9, 0.0,15.9);
    normal = Normal(0.0,1.0, 0.0);
    Rectangular*tall_top_ptr = new Rectangular(p0, a, b, normal);
    tall_top_ptr->setMaterial(matte_ptr3);
    addGeometry(tall_top_ptr);


    // side 1

    p0 = Point3D(42.3,0.0, 24.7);
    a = Vector3D(-15.8,0.0, 4.9);
    b = Vector3D(0.0,33.0, 0.0);
    Rectangular* tall_side_ptr1= new Rectangular(p0, a, b);
    tall_side_ptr1->setMaterial(matte_ptr3);
    addGeometry(tall_side_ptr1);


    // side 2

    p0 = Point3D(26.5,0.0, 29.6);
    a = Vector3D(4.9, 0.0,15.9);
    Rectangular*tall_side_ptr2 = new Rectangular(p0, a, b);
    tall_side_ptr2->setMaterial(matte_ptr3);
    addGeometry(tall_side_ptr2);


    // side 3

    p0 = Point3D(31.4,0.0, 45.5);
    a = Vector3D(15.8,0.0, -4.9);
    Rectangular*tall_side_ptr3 = new Rectangular(p0, a, b);
    tall_side_ptr3->setMaterial(matte_ptr3);
    addGeometry(tall_side_ptr3);


    // side 4

    p0 = Point3D(47.2,0.0, 40.6);
    a = Vector3D(-4.9,0.0, -15.9);
    Rectangular*tall_side_ptr4 = new Rectangular(p0, a, b);
    tall_side_ptr4->setMaterial(matte_ptr3);
    addGeometry(tall_side_ptr4);

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
/*
    在这里添加自旋锁可以解决AO奇怪的斑块问题，因为使用了TBB库的问题，但是直接用太影响性能，所以会独自计算AO不放进材质中
*/
                    mutex.lock();
                    if(areaLightTracer_ptr){
                        pixelColor += areaLightTracer_ptr->trace_ray(camera_ptr->getRay(pp), 0);
                    }
                    pixelColor+= tracer_ptr->trace_ray(camera_ptr->getRay(pp),0);
                    mutex.unlock();
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
	QColor color(int(255.99*pixelColor.r), int(255.99*pixelColor.g), int(255.99*pixelColor.b));
    return color;
}
