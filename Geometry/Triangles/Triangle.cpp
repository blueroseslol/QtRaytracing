﻿#include "Utilities/Constants.h"
#include "Triangle.h"
#include "Utilities/Maths.h"
Triangle::Triangle ():Geometry(),v0(0, 0, 0),v1(0,0,1),v2(1,0,0),normal(0, 1, 0)
{}

Triangle::Triangle (const Point3D& a, const Point3D& b, const Point3D& c):Geometry(),v0(a),v1(b),v2(c)
{
    computeNormal();
}

Triangle::Triangle (const Triangle& triangle):Geometry(triangle),v0(triangle.v0),v1(triangle.v1),v2(triangle.v2),normal(triangle.normal)
{}

Triangle::Triangle(Triangle &&triangle):Geometry(triangle),v0(triangle.v0),v1(triangle.v1),v2(triangle.v2),normal(triangle.normal)
{}

Triangle& Triangle::operator= (const Triangle& rhs) {
	if (this == &rhs)
		return (*this);
    Geometry::operator=(rhs);

	v0 		= rhs.v0;
	v1 		= rhs.v1;
	v2 		= rhs.v2;
	normal 	= rhs.normal;
		
	return (*this);
}

Triangle::~Triangle () {}

void Triangle::computeNormal() {
	normal = (v1 - v0) ^ (v2 - v0);  
	normal.normalize();
}

BBox Triangle::getBoundingBox() {
	double delta = 0.000001; 
	
	return (BBox(min(min(v0.x, v1.x), v2.x) - delta, max(max(v0.x, v1.x), v2.x) + delta, 
				 min(min(v0.y, v1.y), v2.y) - delta, max(max(v0.y, v1.y), v2.y) + delta, 
				 min(min(v0.z, v1.z), v2.z) - delta, max(max(v0.z, v1.z), v2.z) + delta));
}

bool Triangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {	
    double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.direction.x, d = v0.x - ray.origin.x;
    double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.direction.y, h = v0.y - ray.origin.y;
    double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.direction.z, l = v0.z - ray.origin.z;
		
	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;
	
	double inv_denom  = 1.0 / (a * m + b * q + c * s);
	
	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;
	
	if (beta < 0.0)
        return false;
	
	double r = r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;
	
	if (gamma < 0.0 )
        return false;
	
	if (beta + gamma > 1.0)
        return false;
			
	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;
	
	if (t < kEpsilon) 
        return false;
					
	tmin 				= t;
	sr.normal 			= normal;  	
    sr.local_hit_point 	= ray.origin + t * ray.direction;
	
    return true;
}  		

bool Triangle::shadowHit(const Ray& ray, double &tmin) const {
    double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.direction.x, d = v0.x - ray.origin.x;
    double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.direction.y, h = v0.y - ray.origin.y;
    double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.direction.z, l = v0.z - ray.origin.z;
		
	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;
	
	double inv_denom  = 1.0 / (a * m + b * q + c * s);
	
	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;
	
	if (beta < 0.0)
        return false;
	
	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;
	
	if (gamma < 0.0)
        return false;
	
	if (beta + gamma > 1.0)
        return false;
			
	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;
	
	if (t < kEpsilon)
        return false;
					
	tmin = t;
	
    return true;
}

Normal Triangle::getNormal(const Point3D &point) const
{
    return normal;
}
