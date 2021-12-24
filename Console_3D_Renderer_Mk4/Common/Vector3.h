#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3
{
public:
	Vector3();

	// Constructor that sets the Vectors pos
	Vector3(double, double, double);

	Vector3 operator + (Vector3);

	void operator += (Vector3);

	Vector3 operator - (Vector3);

	void operator -= (Vector3);

	// Projection of the vector onto A
	Vector3 projOnto(Vector3);

	// Scalar Projection of the vector onto A
	double scalarProjOnto(Vector3);

	// Returns length of the vector
	double abs();

	// Returns the vector with the same direction and magnitude of 1
	Vector3 normalized();

	// Dot product
	double dot(Vector3);

	// Dot product
	double operator * (Vector3);

	// Scalar multiplication
	Vector3 operator * (double);

	// Scalar multiplication
	void operator *= (double);

	// Scalar division
	Vector3 operator / (double);

	// Scalar division
	void operator /= (double);

	// Cross product
	Vector3 cross(Vector3);

	void set(double, double, double);

	void set(Vector3);

	double x;
	double y;
	double z;
};

// Also scalar multiplication, but oppopsite order
Vector3 operator * (double, Vector3);

#endif
