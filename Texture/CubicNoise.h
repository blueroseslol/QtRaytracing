#ifndef __CUBIC_NOISE__
#define __CUBIC_NOISE__

#include "Utilities/Vector3D.h"
#include "LatticeNoise.h"

//------------------------------------------------------------------------- class CubicNoise

class CubicNoise: public LatticeNoise {		
	public: 
        CubicNoise();
		
		CubicNoise(int octaves);									
		
		CubicNoise(int octaves, float lacunarity, float gain); 	

        CubicNoise(const CubicNoise& cns);

        CubicNoise(CubicNoise&& cns);

        ~CubicNoise();
				
        virtual float valueNoise(const Point3D& p) const;
		
        virtual Vector3D vectorNoise(const Point3D& p) const;
};
//------------------------------------------------------------------------- four_knot_spline

// Cubic interpolation using a Catmull-Rom four knot spline.
// This is templated so that we can use it to interpolate floats and Vector3Ds.
// This is not a class member function.

template<class T> T
fourKnotSpline(const float x, const T knots[]) {
	T c3 = -0.5 * knots[0] + 1.5 * knots[1] - 1.5 * knots[2] + 0.5 * knots[3];
  	T c2 = knots[0] - 2.5 * knots[1] + 2.0 * knots[2] - 0.5 * knots[3];
  	T c1 = 0.5 * (-knots[0] + knots [2]);
  	T c0 = knots[1];
     
    return (T((c3*x + c2)*x + c1)*x + c0);
}
#endif
