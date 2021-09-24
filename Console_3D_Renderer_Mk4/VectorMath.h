#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H

class Vector2
{
public:
	Vector2();

	Vector2(float, float);
	// Constructor which sets x and y

	void operator = (Vector2);
	// Assignment operator

	void set(float, float);

	float x;
	float y;
};

class Vector3
{
public:
	Vector3();

	Vector3(float, float, float);
	// Constructor that sets the Vectors pos

	Vector3 operator + (Vector3);

	void operator += (Vector3);

	Vector3 operator - (Vector3);

	void operator -= (Vector3);

	Vector3 projOnto(Vector3);
	// Projection of the vector onto A

	float scalarProjOnto(Vector3);
	// Scalar Projection of the vector onto A

	float abs(void);
	// overloaded function abs (absolute value)
	// returns length of the vector

	float dot(Vector3);
	// Dot product

	float operator * (Vector3);
	// Also Dot product

	Vector3 operator / (float);
	// scalar division

	Vector3 cross(Vector3);
	// cross product

	void set(float, float, float);

	void set(Vector3);

	float x;
	float y;
	float z;
};

Vector3 operator * (Vector3, float);
Vector3 operator * (float, Vector3);

#endif
