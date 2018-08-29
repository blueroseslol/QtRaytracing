#include "Sphere.h"
#include "math.h"

const double Sphere::kEpsilon = 0.001;

// ---------------------------------------------------------------- default constructor

Sphere::Sphere(void) : center(0.0),radius(1.0)
{}


// ---------------------------------------------------------------- constructor

Sphere::Sphere(Point3D c, double r) : center(c), radius(r)
{}


// ---------------------------------------------------------------- clone

Sphere*
Sphere::clone(void) const {
    return (new Sphere(*this));
}


// ---------------------------------------------------------------- copy constructor

Sphere::Sphere (const Sphere& sphere) : center(sphere.center), radius(sphere.radius)
{}

Sphere::Sphere (Sphere&& sphere) : center(sphere.center), radius(sphere.radius)
{}
// ---------------------------------------------------------------- assignment operator

Sphere&
Sphere::operator= (const Sphere& rhs)
{
    if (this == &rhs)
        return (*this);

//    GeometricObject::operator= (rhs);

    center 	= rhs.center;
    radius	= rhs.radius;

    return (*this);
}

Sphere&
Sphere::operator= (Sphere&& rhs)
{
    if (this == &rhs)
        return (*this);

//    GeometricObject::operator= (rhs);

    center 	= rhs.center;
    radius	= rhs.radius;

    return (*this);
}
// ---------------------------------------------------------------- destructor

Sphere::~Sphere(void) {}


//---------------------------------------------------------------- hit

bool
Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
    double 		t;
    Vector3D	temp 	= ray.origin - center;
    double 		a 		= ray.direction * ray.direction;
    double 		b 		= 2.0 * temp * ray.direction;
    double 		c 		= temp * temp - radius * radius;
    double 		disc	= b * b - 4.0 * a * c;

    if (disc < 0.0)
        return false;
    else {
        double e = sqrt(disc);
        double denom = 2.0 * a;
        t = (-b - e) / denom;    // smaller root

        if (t > kEpsilon) {
            tmin = t;
            sr.normal 	 = (temp + t * ray.direction) / radius;
            sr.local_hit_point = ray.origin + t * ray.direction;
            return (true);
        }

        t = (-b + e) / denom;    // larger root

        if (t > kEpsilon) {
            tmin = t;
            sr.normal   = (temp + t * ray.direction) / radius;
            sr.local_hit_point = ray.origin + t * ray.direction;
            return true;
        }
    }

    return false;
}

bool Sphere::shadowHit(const Ray &ray, float &tMin) const
{
    double 		t;
    Vector3D	temp 	= ray.origin - center;
    double 		a 		= ray.direction * ray.direction;
    double 		b 		= 2.0 * temp * ray.direction;
    double 		c 		= temp * temp - radius * radius;
    double 		disc	= b * b - 4.0 * a * c;

    if (disc < 0.0)
        return false;
    else {
        double e = sqrt(disc);
        double denom = 2.0 * a;
        t = (-b - e) / denom;    // smaller root

        if (t > kEpsilon) {
            tMin = t;
            return true;
        }

        t = (-b + e) / denom;    // larger root

        if (t > kEpsilon) {
            tMin = t;
            return true;
        }
    }
    return false;
}
