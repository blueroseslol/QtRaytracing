#include <QVector>
#include "Utilities/Constants.h"
#include "Geometry/compound.h"

Compound::Compound ():Geometry()
{}

Compound::Compound (const Compound& c):Geometry(c) {
    copyObjects(c.objects);
}

Compound::Compound(Compound &&c)
{

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
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++)
        objects[j]->setMaterial(material_ptr);
}

void Compound::deleteObjects() {
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}	
	
	objects.erase(objects.begin(), objects.end());
}

void Compound::copyObjects(const QVector<Geometry *> &rhs) {
    deleteObjects();
    int num_objects = rhs.size();
	
	for (int j = 0; j < num_objects; j++)
        objects.push_back(rhs[j]->clone());
}

bool Compound::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	double		t; 
	Normal		normal;
	Point3D		local_hit_point;
	bool		hit 		= false;
				tmin 		= kHugeValue;
	int 		num_objects	= objects.size();
	
	for (int j = 0; j < num_objects; j++)
		if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
			hit				= true;
			tmin 			= t;
			material_ptr	= objects[j]->get_material();	// lhs is GeometricObject::material_ptr
			normal			= sr.normal;
			local_hit_point	= sr.local_hit_point;  
		}
	
	if (hit) {
		sr.t				= tmin;
		sr.normal 			= normal;   
		sr.local_hit_point 	= local_hit_point;  
	}
	
    return hit;
}


