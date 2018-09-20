#include "Utilities/Constants.h"
#include "Instance.h"
#include <type_traits>

// initialise the static transformation matrix

Matrix Instance::forwardMatrix;

Instance::Instance():Geometry(),object_ptr(nullptr),invMatrix(),bbox(),transformTheTexture(true)
{
    forwardMatrix.set_identity();
}

Instance::Instance(Geometry* obj_ptr):Geometry(),object_ptr(obj_ptr),invMatrix(),bbox(),transformTheTexture(true)
{
    forwardMatrix.set_identity();
}	

//Instance::Instance (const Instance& instance):Geometry(instance),invMatrix(instance.invMatrix),transformTheTexture(instance.transformTheTexture)
//{
//	if(instance.object_ptr)
//        object_ptr = new std::remove_pointer<decltype(instance.object_ptr)>::type (*instance.object_ptr);
//    else  object_ptr = nullptr;
//}

Instance::Instance(Instance &&instance):Geometry(instance),invMatrix(instance.invMatrix),transformTheTexture(instance.transformTheTexture),object_ptr(instance.object_ptr)
{
    instance.object_ptr=nullptr;
}

Instance::~Instance() {
	if (object_ptr) {
		delete object_ptr;
        object_ptr = nullptr;
	}
}


// ---------------------------------------------------------------- assignment operator

//Instance&
//Instance::operator= (const Instance& rhs) {
//	if (this == &rhs)
//		return (*this);

//    Geometry::operator=(rhs);
		
//	if(object_ptr) {
//		delete object_ptr;
//		object_ptr = NULL;
//	}
	
//	if (rhs.object_ptr)
//		object_ptr = rhs.object_ptr->clone();
//	else
//		object_ptr = NULL;
	
//    invMatrix				= rhs.invMatrix;
//	bbox					= rhs.bbox;
//    transformTheTexture 	= rhs.transformTheTexture;
	
//	return (*this);
//}


//------------------------------------------------------------------ set_object

void 												
Instance::setObject(Geometry* obj_ptr) {
	object_ptr = obj_ptr;
}


//---------------------------------------------------------------- set_bounding_box
// This function is only called when the instance is to be placed in a grid
// It will always be called from a build function

//void
//Instance::computeBoundingBox() {
	
//	// First get the object's untransformed BBox
	
//	BBox object_bbox = object_ptr->get_bounding_box();
	
	
//	// Now apply the affine transformations to the box.
//	// We must apply the transformations to all 8 vertices of the orginal box
//	// and then work out the new minimum and maximum values
	
//	// Construct the eight vertices as 3D points:
	
//	Point3D v[8];
	
//	v[0].x = object_bbox.x0; v[0].y = object_bbox.y0; v[0].z = object_bbox.z0;
//	v[1].x = object_bbox.x1; v[1].y = object_bbox.y0; v[1].z = object_bbox.z0;
//	v[2].x = object_bbox.x1; v[2].y = object_bbox.y1; v[2].z = object_bbox.z0;
//	v[3].x = object_bbox.x0; v[3].y = object_bbox.y1; v[3].z = object_bbox.z0;
	
//	v[4].x = object_bbox.x0; v[4].y = object_bbox.y0; v[4].z = object_bbox.z1;
//	v[5].x = object_bbox.x1; v[5].y = object_bbox.y0; v[5].z = object_bbox.z1;
//	v[6].x = object_bbox.x1; v[6].y = object_bbox.y1; v[6].z = object_bbox.z1;
//	v[7].x = object_bbox.x0; v[7].y = object_bbox.y1; v[7].z = object_bbox.z1;
	
	
//	// Transform these using the forward matrix

//    v[0] = forwardMatrix * v[0];
//    v[1] = forwardMatrix * v[1];
//    v[2] = forwardMatrix * v[2];
//    v[3] = forwardMatrix * v[3];
//    v[4] = forwardMatrix * v[4];
//    v[5] = forwardMatrix * v[5];
//    v[6] = forwardMatrix * v[6];
//    v[7] = forwardMatrix * v[7];

	
//	// Since forward_matrix is a static variable, we must now set it to the unit matrix
//	// This sets it up correctly for the next instance object
	
//    forwardMatrix.set_identity();
	
	
//	// Compute the minimum values
	
//	float x0 = kHugeValue;
//	float y0 = kHugeValue;
//	float z0 = kHugeValue;
		
//	for (int j = 0; j <= 7; j++)  {
//		if (v[j].x < x0)
//			x0 = v[j].x;
//	}
		
//	for (int j = 0; j <= 7; j++) {
//		if (v[j].y < y0)
//			y0 = v[j].y;
//	}
		
//	for (int j = 0; j <= 7; j++) {
//		if (v[j].z < z0)
//			z0 = v[j].z;
//	}
	
//	// Compute the minimum values
	
//	float x1 = -kHugeValue;
//	float y1 = -kHugeValue;
//	float z1 = -kHugeValue;
	
//	for (int j = 0; j <= 7; j++) {
//		if (v[j].x > x1)
//			x1 = v[j].x;
//	}
		
//	for (int j = 0; j <= 7; j++) {
//		if (v[j].y > y1)
//			y1 = v[j].y;
//	}
		
//	for (int j = 0; j <= 7; j++) {
//		if (v[j].z > z1)
//			z1 = v[j].z;
//	}
	
//	// Assign values to the bounding box
	
//	bbox.x0 = x0;
//	bbox.y0 = y0;
//	bbox.z0 = z0;
//	bbox.x1 = x1;
//	bbox.y1 = y1;
//	bbox.z1 = z1;
//}


//---------------------------------------------------------------- get_bounding_box 

BBox Instance::getBoundingBox() {
	return (bbox);
}

//---------------------------------------------------------------- getMaterial
																
Material* Instance::getMaterial() const {
	return (material_ptr);     
}


//---------------------------------------------------------------- set_material
// Here, material_ptr is Geometry::material_ptr

void Instance::setMaterial(Material* m_ptr) {
	material_ptr = m_ptr;
}



//----------------------------------------------------------------------------------------- hit 

bool 	Instance::hit(const Ray& ray, double& t, ShadeRec& sr) const {
	Ray inv_ray(ray);  
    inv_ray.origin = invMatrix * inv_ray.origin;
    inv_ray.direction = invMatrix * inv_ray.direction;
				
	if (object_ptr->hit(inv_ray, t, sr)) {
        sr.normal = invMatrix * sr.normal;
		sr.normal.normalize();				
						
        if (object_ptr->getMaterial())
            material_ptr = object_ptr->getMaterial();
			
        if (!transformTheTexture)
            sr.local_hit_point = ray.origin + t * ray.direction;

		return (true);
	} 

    return (false);
}

bool Instance::shadowHit(const Ray &ray, double &tmin) const
{
    Ray inv_ray(ray);
    inv_ray.origin = invMatrix * inv_ray.origin;
    inv_ray.direction = invMatrix * inv_ray.direction;

    if (object_ptr->shadowHit(inv_ray, tmin)) {
        return (true);
    }
    return (false);
}


//-------------------------------------------------------------------------------- scale

void Instance::scale(const Vector3D& s) {

	Matrix	inv_scaling_matrix;			// temporary inverse scaling matrix
	
	inv_scaling_matrix.m[0][0] = 1.0 / s.x;
	inv_scaling_matrix.m[1][1] = 1.0 / s.y;
	inv_scaling_matrix.m[2][2] = 1.0 / s.z;

    invMatrix = invMatrix * inv_scaling_matrix;

	Matrix	scaling_matrix;				// temporary scaling matrix
	
	scaling_matrix.m[0][0] = s.x;
	scaling_matrix.m[1][1] = s.y;
	scaling_matrix.m[2][2] = s.z;
	
    forwardMatrix = scaling_matrix * forwardMatrix;
}


//-------------------------------------------------------------------------------- scale

void Instance::scale(const double a, const double b, const double c) {

	Matrix inv_scaling_matrix;					// temporary inverse scaling matrix
	
	inv_scaling_matrix.m[0][0] = 1.0 / a;
	inv_scaling_matrix.m[1][1] = 1.0 / b;
	inv_scaling_matrix.m[2][2] = 1.0 / c;
	
    invMatrix = invMatrix * inv_scaling_matrix;

	Matrix scaling_matrix;						// temporary scaling matrix
	
	scaling_matrix.m[0][0] = a;
	scaling_matrix.m[1][1] = b;
	scaling_matrix.m[2][2] = c;
	
    forwardMatrix = scaling_matrix * forwardMatrix;
}


//-------------------------------------------------------------------------------- translate

void Instance::translate(const Vector3D& trans) {

	Matrix inv_translation_matrix;				// temporary inverse translation matrix	
			
	inv_translation_matrix.m[0][3] = -trans.x;
	inv_translation_matrix.m[1][3] = -trans.y;
	inv_translation_matrix.m[2][3] = -trans.z;
					
    invMatrix = invMatrix * inv_translation_matrix;
	
	Matrix translation_matrix;					// temporary translation matrix	
	
	translation_matrix.m[0][3] = trans.x;
	translation_matrix.m[1][3] = trans.y;
	translation_matrix.m[2][3] = trans.z;
	
    forwardMatrix = translation_matrix * forwardMatrix;
}


//-------------------------------------------------------------------------------- translate

void Instance::translate(const double dx, const double dy, const double dz) {

	Matrix inv_translation_matrix;				// temporary inverse translation matrix	
			
	inv_translation_matrix.m[0][3] = -dx;
	inv_translation_matrix.m[1][3] = -dy;
	inv_translation_matrix.m[2][3] = -dz;
					
    invMatrix = invMatrix * inv_translation_matrix;
	
	Matrix translation_matrix;					// temporary translation matrix	
	
	translation_matrix.m[0][3] = dx;
	translation_matrix.m[1][3] = dy;
	translation_matrix.m[2][3] = dz;
	
    forwardMatrix = translation_matrix * forwardMatrix;
}



//-------------------------------------------------------------------------------- rotate_x

void Instance::rotateX(const double theta) {

	double sin_theta = sin(theta * PI_ON_180);
	double cos_theta = cos(theta * PI_ON_180);
	
	Matrix inv_x_rotation_matrix;					// temporary inverse rotation matrix about x axis
	
	inv_x_rotation_matrix.m[1][1] = cos_theta;
	inv_x_rotation_matrix.m[1][2] = sin_theta;   	
	inv_x_rotation_matrix.m[2][1] = -sin_theta;  
	inv_x_rotation_matrix.m[2][2] = cos_theta;		
					
    invMatrix = invMatrix * inv_x_rotation_matrix;
	
	Matrix x_rotation_matrix;						// temporary rotation matrix about x axis
	
	x_rotation_matrix.m[1][1] = cos_theta;
	x_rotation_matrix.m[1][2] = -sin_theta;
	x_rotation_matrix.m[2][1] = sin_theta;
	x_rotation_matrix.m[2][2] = cos_theta;
				
    forwardMatrix = x_rotation_matrix * forwardMatrix;
}


//-------------------------------------------------------------------------------- rotate_y

void Instance::rotateY(const double theta) {

	double sin_theta = sin(theta * PI / 180.0);
	double cos_theta = cos(theta * PI / 180.0);

	Matrix inv_y_rotation_matrix;					// temporary inverse rotation matrix about y axis
	
	inv_y_rotation_matrix.m[0][0] = cos_theta;   
	inv_y_rotation_matrix.m[0][2] = -sin_theta;  
	inv_y_rotation_matrix.m[2][0] = sin_theta;
	inv_y_rotation_matrix.m[2][2] = cos_theta;		
					
    invMatrix = invMatrix * inv_y_rotation_matrix;
	
	Matrix y_rotation_matrix;						// temporary rotation matrix about x axis
	
	y_rotation_matrix.m[0][0] = cos_theta;
	y_rotation_matrix.m[0][2] = sin_theta;
	y_rotation_matrix.m[2][0] = -sin_theta;
	y_rotation_matrix.m[2][2] = cos_theta;
				
    forwardMatrix = y_rotation_matrix * forwardMatrix;
}



//-------------------------------------------------------------------------------- rotate_z

void Instance::rotateZ(const double theta) {
	double sin_theta = sin(theta * PI / 180.0);
	double cos_theta = cos(theta * PI / 180.0);

	Matrix inv_z_rotation_matrix;					// temporary inverse rotation matrix about y axis	
	
	inv_z_rotation_matrix.m[0][0] = cos_theta;
	inv_z_rotation_matrix.m[0][1] = sin_theta;   	
	inv_z_rotation_matrix.m[1][0] = -sin_theta;  
	inv_z_rotation_matrix.m[1][1] = cos_theta;	
					
    invMatrix = invMatrix * inv_z_rotation_matrix;
	
	Matrix z_rotation_matrix;						// temporary rotation matrix about y axis
	
	z_rotation_matrix.m[0][0] = cos_theta;
	z_rotation_matrix.m[0][1] = -sin_theta;
	z_rotation_matrix.m[1][0] = sin_theta;
	z_rotation_matrix.m[1][1] = cos_theta;
				
    forwardMatrix = z_rotation_matrix * forwardMatrix;
}


//-------------------------------------------------------------------------------- shear

void	Instance::shear(const Matrix& s) {
	
	Matrix inverse_shearing_matrix;    // inverse shear matrix
	
	// discriminant

	double d = 1.0 	- s.m[1][0] * s.m[0][1] - s.m[2][0] * s.m[0][2]  - s.m[2][1] * s.m[1][2]
					+ s.m[1][0] * s.m[2][1] * s.m[0][2] + s.m[2][0] * s.m[0][1] * s.m[2][1];
					
	// diagonals
	
	inverse_shearing_matrix.m[0][0] = 1.0 - s.m[2][1] * s.m[1][2];
	inverse_shearing_matrix.m[1][1] = 1.0 - s.m[2][0] * s.m[0][2];
	inverse_shearing_matrix.m[2][2] = 1.0 - s.m[1][0] * s.m[0][1];
	inverse_shearing_matrix.m[3][3] = d;
	
	// first row
	
	inverse_shearing_matrix.m[0][1] = -s.m[1][0] + s.m[2][0] * s.m[1][2];
	inverse_shearing_matrix.m[0][2] = -s.m[2][0] + s.m[1][0] * s.m[2][1];
	
	// second row
	
	inverse_shearing_matrix.m[1][0] = -s.m[0][1] + s.m[2][1] * s.m[0][2];
	inverse_shearing_matrix.m[1][2] = -s.m[2][1] + s.m[2][0] * s.m[0][1];
	
	// third row
	
	inverse_shearing_matrix.m[2][0] = -s.m[0][2] + s.m[0][1] * s.m[1][2];
	inverse_shearing_matrix.m[2][1] = -s.m[1][2] + s.m[1][0] * s.m[0][2] ;
	
	// divide by discriminant
	
	inverse_shearing_matrix = inverse_shearing_matrix / d;
	
    invMatrix = invMatrix * inverse_shearing_matrix;
	
    forwardMatrix = s * forwardMatrix;
}
