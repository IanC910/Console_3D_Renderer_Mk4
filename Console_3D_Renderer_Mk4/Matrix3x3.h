#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#include "Matrix.h"
#include "Vec3.h"

class Matrix3x3 : public Matrix
{
public:

	// Default Constructor
	Matrix3x3();

	// Constructor with 3 column vectors of type Vec3 as arguments
	Matrix3x3(Vec3, Vec3, Vec3);

	void setColumnVectors(Vec3, Vec3, Vec3);

	double determinant();

	Matrix3x3 inverse();

};

#endif