#include <math.h>
#include "VectorMath.h"


// Vector2
void Vector2::set(float initX, float initY)
{
	x = initX;
	y = initY;
}

Vector2::Vector2()
{
	set(0, 0);
}

Vector2::Vector2(float initX, float initY)
{
	set(initX, initY);
}

void Vector2::operator = (Vector2 A)
{
	x = A.x;
	y = A.y;
}



// Vector3
Vector3::Vector3(float initX, float initY, float initZ)
{
	set(initX, initY, initZ);
}

Vector3::Vector3()
{
	set(0, 0, 0);
}

// Vector Operators

Vector3 Vector3::operator + (Vector3 vec)
{
	return Vector3(x + vec.x, y + vec.y, z + vec.z);
}

void Vector3::operator += (Vector3 vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
}


Vector3 Vector3::operator - (Vector3 vec)
{
	return Vector3(x - vec.x, y - vec.y, z - vec.z);
}

void Vector3::operator -= (Vector3 vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
}


Vector3 Vector3::projOnto(Vector3 vec)
{
	return vec * (float)((double)dot(vec) / pow((double)vec.abs(), 2.0));
}


float Vector3::scalarProjOnto(Vector3 vec)
{
	return dot(vec)/vec.abs();
}


float Vector3::abs()
{
	return (float)sqrt((double)x * (double)x + (double)y * (double)y + (double)z * (double)z);
}


float Vector3::dot(Vector3 vec) // Dot product
{
	return (x * vec.x + y * vec.y + z * vec.z);
}


float Vector3::operator * (Vector3 vec) // veclso Dot product
{
	return (x * vec.x + y * vec.y + z * vec.z);
}

Vector3 Vector3::operator / (float divisor) // scalar division
{
	return Vector3(x / divisor, y / divisor, z / divisor);
}


Vector3 Vector3::cross(Vector3 vec)
{
	return Vector3((y * vec.z - z * vec.y), (z * vec.x - x * vec.z), (x * vec.y - y * vec.x));
}


void Vector3::set(float initX, float initY, float initZ)
{
	x = initX;
	y = initY;
	z = initZ;
}

void Vector3::set(Vector3 v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

Vector3 operator * (Vector3 vec, float multiplier)
{
	return Vector3(vec.x * multiplier, vec.y * multiplier, vec.z * multiplier);
}

Vector3 operator * (float multiplier, Vector3 vec) // Needed so that both orders of operands work
{
	return vec * multiplier;
}
