#ifndef SPHERE_H
#define SPHERE_H
#include "Geometry/Geometry.h"

class Sphere : public Geometry
{
public:

        Sphere();   									// Default constructor

        Sphere(Point3D center, double r);					// Constructor

        Sphere(const Sphere& sphere); 						// Copy constructor
        Sphere(Sphere&& sphere);

        virtual Sphere* 									// Virtual copy constructor
        clone() const;

        virtual												// Destructor
        ~Sphere();

        Sphere& 											// assignment operator
        operator= (const Sphere& sphere);
        Sphere& 											// assignment operator
        operator= (Sphere&& sphere);

        void
        set_center(const Point3D& c);

        void
        set_center(const double x, const double y, const double z);

        void
        set_radius(const double r);

        virtual bool
        hit(const Ray& ray, double& t, ShadeRec& s) const;

    private:

        Point3D 	center;   			// center coordinates as a point
        double 		radius;				// the radius

        static const double kEpsilon;   // for shadows and secondary rays
};


inline void
Sphere::set_center(const Point3D& c) {
    center = c;
}

inline void
Sphere::set_center(const double x, const double y, const double z) {
    center.x = x;
    center.y = y;
    center.z = z;
}

inline void
Sphere::set_radius(const double r) {
    radius = r;
}
#endif // SPHERE_H
