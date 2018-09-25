#ifndef __COMPOUND__
#define __COMPOUND__
#include <QVector>
#include "Geometry/Geometry.h"

class Compound: public Geometry {
public:

    Compound();

    Compound(const Compound& c);

    Compound(Compound&& c);

    ~Compound ();

//    Compound& operator= (const Compound& c);

    virtual void setMaterial(Material* material_ptr);

    virtual void addObject(Geometry* object_ptr);

    int getNumObjects();

    virtual bool hit(const Ray& ray, double& tmin, ShadeRec& s) const;

    virtual bool shadowHit(const Ray &ray, double &tmin) const;
protected:
    QVector<Geometry*> objects;
private:
    void deleteObjects();

    void copyObjects(const QVector<Geometry*>& rhs);
};

inline int
Compound::getNumObjects() {
	return (objects.size());
}
#endif
