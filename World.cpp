#include "World.h"
#include <QtGlobal>
#include "Utilities/Constants.h"
#include "Tracer/singlesphere.h"
#include <QColor>
World::World()
{

}

void World::build(){
    vp.set_hres(200);
    vp.set_vres(200);
    vp.set_pixel_size(1.0);
    vp.set_gamma(1.0);

    background_color=qMove(RGBColor());
    tracer_ptr=new SingleSphere(this);
    sphere.set_center(Point3D(10.0,10.0,0.0));
    sphere.set_radius(85.0);
}

QImage* World::render_scene() {
    RGBColor pixel_color;
    Ray ray;
    double zw=100;
    double x,y;

//    image=new QImage(vp.vres,vp.hres,QImage::Format_RGB888);

//    for(int r=0;r<vp.vres;r++){
//        for(int c=0;c<=vp.hres;c++){
//            x=vp.s*(c-0.5*(vp.hres-1.0));
//            y=vp.s*(r-0.5*(vp.vres-1.0));

    image=new QImage(vp.vres,vp.hres,QImage::Format_RGB888);

    for(int r=0;r<vp.vres;r++){
        for(int c=0;c<=vp.hres;c++){
//            x=vp.s*(c-0.5*(vp.hres-1.0));
//            y=vp.s*(r-0.5*(vp.vres-1.0));

            x=vp.s*r/vp.vres;
            y=vp.s*c/vp.hres;

            ray.origin=Point3D(x,y,zw);
            pixel_color=tracer_ptr->trace_ray(ray);
            //Gamma映射
            //displace_pixel(r,c,pixel_color);
            image->setPixelColor(x,y,QColor(pixel_color.r,pixel_color.g,pixel_color.b));
        }
    }

return image;
}
