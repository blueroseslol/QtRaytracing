#ifndef __INSTANCE__
#define __INSTANCE__

#include "Geometry/Geometry.h"
#include "Utilities/Matrix.h"

class Instance: public Geometry {
	public:
		
        Instance();
		
        Instance(Geometry* obj_ptr);
		
        Instance(const Instance& instance);

        Instance(Instance&& instance);

        virtual ~Instance();
		
//        Instance& operator= (const Instance& rhs);
				
        void 	setObject(Geometry* obj_ptr);
		
        void transformTexture(const bool transform);
			
        virtual void computeBoundingBox();
		
        virtual BBox getBoundingBox();
											
        virtual Material* getMaterial() const;
				
        virtual void setMaterial(Material* materialPtr);
				
        virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

        virtual bool shadowHit(const Ray &ray, double &tmin) const;
		
        void translate(const Vector3D& trans);
		
        void translate(const double dx, const double dy, const double dz);
		
        void scale(const Vector3D& s);
		
        void scale(const double a, const double b, const double c);
		
        virtual void rotateX(const double r);
		
        virtual void rotateY(const double r);
		
        virtual void rotateZ(const double r);
		
        void	shear(const Matrix& m);
	private:
        Geometry*	object_ptr;				// object to be transformed
        Matrix invMatrix;		    	// inverse transformation matrix
        static Matrix forwardMatrix; 		// transformation matrix
        BBox	bbox;					// transformed object's bounding box
        bool	transformTheTexture;	// do we transform the texture?
};

inline void
Instance::transformTexture(const bool transform) {
    transformTheTexture = transform;
}	
#endif
