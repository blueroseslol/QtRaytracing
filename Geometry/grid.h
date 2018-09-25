#ifndef __GRID__
#define __GRID__
#include "Geometry/Compound.h"
#include "Utilities/ShadeRec.h"
#include "Utilities/Mesh.h"

class Grid: public Compound {										  	
public:

    Grid();

    Grid(Mesh* _mesh_ptr);

//    virtual Grid*
//    clone(void) const;

    Grid(const Grid& rg);

    Grid(Grid&& rg);

    Grid& operator= (const Grid& rhs);

    virtual ~Grid();

    virtual BBox getBoundingBox();

//    void readFlatTriangles(char* file_name);

//    void readSmoothTriangles(char* file_name);

//    void tessellateFlatSphere(const int horizontal_steps, const int vertical_steps);

//    void tessellateSmoothSphere(const int horizontal_steps, const int vertical_steps);

    virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

    virtual bool shadowHit(const Ray &ray, double &tmin) const;

    void setupCells();

    void reverseMeshNormals();

    void storeMaterial(Material* material, const int index);

private:

    QVector<Geometry*>	cells;			// grid of cells
    int							nx, ny, nz;    	// number of cells in the x, y, and z directions
    BBox						bbox;			// bounding box
    Mesh*						mesh_ptr;		// holds triangle data
    bool						reverseNormal;	// some PLY files have normals that point inwards

    Point3D findMinBounds();

    Point3D findMaxBounds();

    void readPlyFile(char* file_name, const int triangle_type);

//    void  computeMeshNormals();
};


// ------------------------------------------------------------------------------ store_material

inline void Grid::reverseMeshNormals() {
    reverseNormal = true;
}


// ------------------------------------------------------------------------------ store_material
// stores the material in the specified object
// this is called from the Rosette and Archway classes, which inherit from Grid

inline void Grid::storeMaterial(Material* material_ptr, const int index) {
    objects[index]->setMaterial(material_ptr);
}
#endif
