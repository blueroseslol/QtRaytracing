#ifndef PLANE_H
#define PLANE_H
#include "Geometry/Geometry.h"

class Plane : public Geometry
{
public:
    Plane();   												// default constructor

    Plane(const Point3D& point, const Normal& normal);			// constructor

    Plane(const Plane& plane);
    // copy constructor
    Plane(Plane&& plane);

//    virtual Plane* 												// virtual copy constructor
//    clone() const;

    Plane& 														// assignment operator
    operator= (const Plane& rhs);
    Plane& 														// assignment operator
    operator= (Plane&& rhs);

    virtual														// destructor
    ~Plane();

    virtual bool
    hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

private:
    Point3D 	a;   				// point through which plane passes
    Normal 	n;					// normal to the plane

    static const double kEpsilon;   // for shadows and secondary rays
};

#endif // PLANE_H
