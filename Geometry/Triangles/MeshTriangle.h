#ifndef __MESH_TRIANGLE__
#define __MESH_TRIANGLE__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This file contains the declaration of the class MeshTriangle
// Triangle classes derived from MeshTriangle, such as FlatMeshTriangle and SmoothMeshTriangle, 
// are stored in a regular grid for rendering triangle meshes
// A mesh triangle stores integer indices into the vertices array in a Mesh object
// A mesh triangle also stores a pointer to the Mesh object
// A mesh triangle also stores the normal for use in FlatMeshTriangle and for 
// computing the average normal at each vertex for SmoothMeshTriangles
// A mesh triangle defines the shadow hit function because this is independent of whether the
// triangle is flat shaded or smooth shaded or uv mapped or not uv mapped

// MeshTriangle doesn't inherit from the Triangle class discussed in Chapter 19, 
// because Triangle stores the vertices and a normal

#include "Geometry/Geometry.h"
#include "Utilities/Mesh.h"

class MeshTriangle: public Geometry {
	public:

		Mesh* 		mesh_ptr;					// stores all the data
		int			index0, index1, index2;  	// indices into the vertices array in the mesh
		Normal		normal;					
		float		area;						// required for translucency
	
	public:
		
        MeshTriangle();
		
		MeshTriangle(Mesh* _mesh_ptr, const int i1, const int i2, const int i3);		
	
		MeshTriangle(const MeshTriangle& mt); 					

        virtual ~MeshTriangle();

        MeshTriangle& operator= (const MeshTriangle& rhs);
		
        virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const = 0;
		
        virtual	bool shadowHit(const Ray& ray, double& tmin) const;
		
        void computeNormal(const bool reverse_normal);
				
        virtual Normal getNormal(void) const;

        virtual BBox getBoundingBox();
		
	protected:
        float interpolateU(const float beta, const float gamma) const;
		
        float interpolateV(const float beta, const float gamma) const;
};

#endif

