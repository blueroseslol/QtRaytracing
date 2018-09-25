#include <QVector>
#include "Utilities/Constants.h"
#include "Geometry/compound.h"

Compound::Compound ():Geometry()
{}

Compound::Compound (const Compound& c):Geometry(c),objects(c.objects) {}

Compound::Compound(Compound &&c):Geometry(c),objects(QVector<Geometry*>(c.objects))
{
    c.objects.erase(c.objects.begin(),c.objects.end());
}

//Compound& Compound::operator= (const Compound& rhs) {
//	if (this == &rhs)
//		return (*this);

//	GeometricObject::operator= (rhs);
	
//    copyObjects(rhs.objects);

//	return (*this);
//}

Compound::~Compound() {
    deleteObjects();
}

void Compound::addObject(Geometry *object_ptr) {
	objects.push_back(object_ptr);	
}

void Compound::setMaterial(Material* material_ptr) {
    for (int j = 0; j < objects.size(); j++)
        objects[j]->setMaterial(material_ptr);
}

void Compound::deleteObjects() {
    for (int j = 0; j < objects.size(); j++) {
		delete objects[j];
        objects[j] = nullptr;
	}	
	objects.erase(objects.begin(), objects.end());
}

void Compound::copyObjects(const QVector<Geometry *> &rhs) {
    deleteObjects();
    for (int j = 0; j < rhs.size(); j++)
        objects=QVector<Geometry*>(rhs);
}

bool Compound::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
    double	t;
    Normal	normal;
    Point3D	local_hit_point;
    bool	hit=false;
    tmin=kHugeValue;

    for (int j = 0; j < objects.size(); j++)
        if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
            hit	= true;
            tmin= t;
            material_ptr=objects[j]->getMaterial();	// lhs is GeometricObject::material_ptr
            normal=sr.normal;
            local_hit_point=sr.local_hit_point;
        }

    if (hit) {
        sr.t= tmin;
        sr.normal= normal;
        sr.local_hit_point= local_hit_point;
    }
    return hit;
}

bool Compound::shadowHit(const Ray &ray, double &tmin) const
{
    double	t;
    bool	hit=false;
    tmin=kHugeValue;

    for (int j = 0; j < objects.size(); j++)
        if (objects[j]->shadowHit(ray, t) && (t < tmin)) {
            hit	= true;
            tmin = t;
        }
    return hit;
}

//BBox Compound::getBoundingBox()
//{
//    qDebug()<<"编写对应BBox逻辑";
//    return BBox();
//}


