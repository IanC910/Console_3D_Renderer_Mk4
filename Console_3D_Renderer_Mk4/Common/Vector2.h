#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
public:
	Vector2();
	
	// Constructor that sets the vector's position
	Vector2(double, double);

	Vector2 operator + (Vector2);

	void operator += (Vector2);

	Vector2 operator - (Vector2);

	void operator -= (Vector2);

	// Projection of the vector onto A
	Vector2 projOnto(Vector2);

	// Scalar projection of the vector onto A
	double scalarProjOnto(Vector2);

	// Returns length of the vector
	double abs();

	// Returns the vector with the same direction and magnitude of 1
	Vector2 normalized();

	// Dot product
	double dot(Vector2);
	
	// Dot product
	double operator * (Vector2);
	
	// Scalar multiplication
	Vector2 operator * (double);

	// Scalar multiplication
	void operator *= (double);

	// Scalar division
	Vector2 operator / (double);

	// Scalar division
	void operator /= (double);

	void set(double, double);

	void set(Vector2);

	double x;
	double y;
};

// Also scalar multiplication, but oppopsite order
Vector2 operator * (double, Vector2);

#endif