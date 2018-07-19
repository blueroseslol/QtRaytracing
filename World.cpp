#include "World.h"
#include <QtGlobal>
#include "Utilities/Constants.h"
#include "Tracer/singlesphere.h"
#include <QColor>
#include <QFile>
#include <QTextStream>
#include "Utilities/Maths.h"
#include "Utilities/Vector3D.h"
#include <QDebug>
World::World()
{

}

void World::build(){
    vp.set_hres(100);
    vp.set_vres(200);
    vp.set_pixel_size(1.0);
    vp.set_gamma(1.0);

    background_color=qMove(RGBColor());
    tracer_ptr=new SingleSphere(this);
    sphere.set_center(Point3D(0.0,0.0,-1));
    sphere.set_radius(0.5);
}

QImage* World::render_scene() {
    RGBColor pixel_color;
    Ray ray;
    int nx = 200;
    int ny = 100;
    QImage *image=new QImage(nx,ny,QImage::Format_RGB888);

    QFile file("result.ppm");
    if (!file.open(QFile::WriteOnly | QFile :: Truncate))
        return nullptr;
    QTextStream out(&file);
    out << "P3\n" <<nx << " " << ny << "\n255\n";


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

            int ir = int(255.99*color.r);
            int ig = int(255.99*color.g);
            int ib = int(255.99*color.b);
            out << ir << " " << ig << " " << ib << "\n";
            image->setPixelColor(i,j,QColor(ir,ig,ib));
        }
    }
    file.close();

return image;
}
