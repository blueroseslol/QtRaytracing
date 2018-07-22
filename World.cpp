#include "World.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <QDebug>
#include <QtConcurrent>
#include <QFutureSynchronizer>
//#include "Tracer/singlesphere.h"
#include "Tracer/mutipleobjects.h"

World::World(RenderSetting *_setting):setting(_setting),tracer_ptr(nullptr)
{

}

World::~World(){
    if(tracer_ptr)
        delete tracer_ptr;
}

void World::build(){
    tracer_ptr=new MutipleObjects(this);
    Sphere *sphere=new Sphere(Point3D(0.0,0.0,-1),0.5);
    sphere->setColor(RGBColor(1.0,0,0));
    addGeometry(sphere);

    Sphere *sphere1=new Sphere(Point3D(0.2,0.2,-0.8),0.3);
    sphere1->setColor(RGBColor(0,1.0,0));
    addGeometry(sphere1);
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
/*
    这里使用QtConcurrent并行执行渲染任务
*/
    QtConcurrent::run([this](){
        Ray ray;
        RGBColor pixelColor;
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
        //for (int j = ny - 1; j >= 0; j--){
        for (int j = 0; j < ny; j++){
            for (int i=0;i<nx;i++){

                for(int k=0;k<setting->numSamples;k++){

                    sp=setting->samplerPtr->sampleUnitSquare();
                    float u = float(i) / float(nx);
                    float v = float(j) / float(ny);
                    ray.origin=origin;
                    ray.direction=lower_left_corner+u*horizontal+v*vertical;

                    pixelColor+= tracer_ptr->trace_ray(ray);


                }
                pixelColor/=setting->numSamples;
                currentPixelNum++;
                emit pixelComplete(i,j,currentPixelNum*100/allPixelNum,QColor( int(255.99*color.r), int(255.99*color.g), int(255.99*color.b)));
            }
        }
        emit renderComplete();
    });
}
