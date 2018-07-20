#include "World.h"
#include <QDebug>
#include <QtConcurrent>
#include <QFutureSynchronizer>
#include "Tracer/singlesphere.h"
World::World(RenderSetting *_setting):setting(_setting),tracer_ptr(nullptr)
{

}

World::~World(){
    if(tracer_ptr)
        delete tracer_ptr;
}

void World::build(){
    tracer_ptr=new SingleSphere(this);
    sphere.set_center(Point3D(0.0,0.0,-1));
    sphere.set_radius(0.5);
}

void World::render_scene() {
/*
    这里使用QtConcurrent并行执行渲染任务
*/
    QtConcurrent::run([this](){
        Ray ray;
        int nx = setting->imageWidth;
        int ny =  setting->imageHeight;

        Vector3D lower_left_corner(-2.0, -1.0, -1.0);
        Vector3D horizontal(4.0, 0.0, 0.0);
        Vector3D vertical(0.0, 2.0, 0.0);
        Point3D origin(0.0, 0.0, 0.0);
        //for (int j = ny - 1; j >= 0; j--){
        for (int j = 0; j < ny; j++){
            for (int i=0;i<nx;i++){
                float u = float(i) / float(nx);
                float v = float(j) / float(ny);
                ray.origin=origin;
                ray.direction=lower_left_corner+u*horizontal+v*vertical;

                RGBColor color= tracer_ptr->trace_ray(ray);
                //int ir = int(255.99*color.r);
                //int ig = int(255.99*color.g);
                //int ib = int(255.99*color.b);

                emit pixelComplete(i,j,QColor( int(255.99*color.r), int(255.99*color.g), int(255.99*color.b)));
            }
        }
    });
}
