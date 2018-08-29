#include "plane.h"
#include "QDebug"
const double Plane::kEpsilon = 0.001;

// ----------------------------------------------------------------------  default constructor

Plane::Plane() : a(0.0),n(0, 1, 0)
{}


// ----------------------------------------------------------------------  constructor

Plane::Plane(const Point3D& point, const Normal& normal) : a(point),n(normal)
{
        n.normalize();
}


// ---------------------------------------------------------------- copy constructor

Plane::Plane(const Plane& plane) :a(plane.a),n(plane.n)
{}

Plane::Plane(Plane&& plane) :a(plane.a),n(plane.n)
{}
// ---------------------------------------------------------------- clone

//Plane*
//Plane::clone(void) const {
//    return (new Plane(*this));
//}


// ---------------------------------------------------------------- assignment operator

Plane&
Plane::operator= (const Plane& rhs)	{

    if (this == &rhs)
        return (*this);

    Geometry::operator= (rhs);

    a = rhs.a;
    n = rhs.n;

    return (*this);
}

Plane&
Plane::operator= (Plane&& rhs)	{

    if (this == &rhs)
        return (*this);

    Geometry::operator= (rhs);

    a = rhs.a;
    n = rhs.n;

    return (*this);
}
// ---------------------------------------------------------------- destructor

Plane::~Plane()
{}


// ----------------------------------------------------------------- hit

bool
Plane::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
    double t = (a - ray.origin) * n / (ray.direction * n);

    if (t > kEpsilon) {
        tmin = t;
        sr.normal = n;
        sr.local_hit_point = ray.origin + t * ray.direction;

        return (true);
    }

    return(false);
}

bool Plane::shadowHit(const Ray &ray, float &tMin) const
{
    float t=(a-ray.origin)*n/(ray.direction*n);
    if(t>kEpsilon){
        tMin=t;
        return true;
    }else{
        return false;
    }
}


