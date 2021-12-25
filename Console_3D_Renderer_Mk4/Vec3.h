#ifndef VEC3_H
#define VEC3_H

#include <vector>

class Vec3
{
public:

	double x;
	double y;
	double z;

	// Default constructor
	Vec3();

	// Constructor that sets the Vectors pos
	Vec3(double, double, double);

	/////////////////////////////
	// Vector operations
	/////////////////////////////

	Vec3 operator + (Vec3);

	void operator += (Vec3);

	Vec3 operator - (Vec3);

	void operator -= (Vec3);

	// Projection of the vector onto A
	Vec3 projOnto(Vec3);

	// Scalar Projection of the vector onto A
	double scalarProjOnto(Vec3);

	// Returns length of the vector
	double abs();

	// Returns the vector with the same direction and magnitude of 1
	Vec3 normalized();

	// Dot product
	double dot(Vec3);

	// Dot product
	double operator * (Vec3);

	// Cross product
	Vec3 cross(Vec3);

	void set(Vec3);

	/////////////////////////////
	// Scalar operations
	/////////////////////////////

	// Scalar multiplication
	Vec3 operator * (double);

	// Scalar multiplication
	void operator *= (double);

	// Scalar division
	Vec3 operator / (double);

	// Scalar division
	void operator /= (double);

	void set(double, double, double);
};

// Also scalar multiplication, but oppopsite order
Vec3 operator * (double, Vec3);

#endif
