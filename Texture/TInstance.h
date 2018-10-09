#ifndef __TINSTANCE__
#define __TINSTANCE__

#include "Utilities/Constants.h"
#include "Texture.h"

class TInstance : public Texture {
public:
    TInstance();

	TInstance(Texture* tex);

    TInstance(const TInstance& it);

    TInstance(TInstance&& it);

    ~TInstance();

    void setTexture(Texture* t_ptr);

    virtual RGBColor getColor(const ShadeRec& sr) const;

	// affine tranformation functions:

	void scale(const double sx, const double sy, const double sz);

	void scale(const double s);

	void translate(const double tx, const double ty, const double tz);
private:
	Texture* 	texture_ptr;	// texture being transformed
    Matrix		inv_matrix;		// inverse transformation matrix
};
#endif
