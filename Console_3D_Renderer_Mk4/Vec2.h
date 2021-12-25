#ifndef VEC2_H
#define VEC2_H

class Vec2
{
public:

	double x;
	double y;

	// Default constructor
	Vec2();
	
	// Constructor that sets the vector's position
	Vec2(double, double);

	/////////////////////////////
	// Vector operations
	/////////////////////////////

	Vec2 operator + (Vec2);

	void operator += (Vec2);

	Vec2 operator - (Vec2);

	void operator -= (Vec2);

	// Projection of the vector onto A
	Vec2 projOnto(Vec2);

	// Scalar projection of the vector onto A
	double scalarProjOnto(Vec2);

	// Returns length of the vector
	double abs();

	// Returns the vector with the same direction and magnitude of 1
	Vec2 normalized();

	// Dot product
	double dot(Vec2);
	
	// Dot product
	double operator * (Vec2);

	void set(Vec2);

	/////////////////////////////
	// Scalar operations
	/////////////////////////////
	
	// Scalar multiplication
	Vec2 operator * (double);

	// Scalar multiplication
	void operator *= (double);

	// Scalar division
	Vec2 operator / (double);

	// Scalar division
	void operator /= (double);

	void set(double, double);
};

// Also scalar multiplication, but oppopsite order
Vec2 operator * (double, Vec2);

#endif