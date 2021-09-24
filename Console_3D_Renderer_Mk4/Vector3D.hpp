#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3D
{
public:

	Vector3D(float tempX, float tempY, float tempZ);
	// Constructor that sets the Vectors pos

	Vector3D(void);
	// Default Constructor
	// Vector Operators ===================================

	Vector3D operator+(Vector3D A);

	void operator+=(Vector3D A);

	Vector3D operator-(Vector3D A);

	void operator-=(Vector3D A);

	Vector3D projOnto(Vector3D A);
	// Projection of the vector onto A

	float scalarProjOnto(Vector3D A);
	// Scalar Projection of the vector onto A

	float abs(void);
	// overloaded function abs (absolute value)
	// returns length of the vector

	float dot(Vector3D A);
	// Dot product

	float operator*(Vector3D A);
	// Also Dot product

	Vector3D operator*(float a);
	// scalar multiplication

	Vector3D operator/(float a);
	// scalar division

	Vector3D cross(Vector3D A);
	// cross product

	// Other content ======================================

	void set(float tempX, float tempY, float tempZ);

	void set(Vector3D v);

	float x;
	float y;
	float z;
};

#endif
