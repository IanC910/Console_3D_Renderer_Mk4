#include <math.h>
#include "VectorMath.h"


// Vector2
Vector2::Vector2()
{
	set(0, 0);
}

Vector2::Vector2(float initX, float initY)
{
	set(initX, initY);
}

Vector2 Vector2::operator + (Vector2 vec)
{
	return Vector2(x + vec.x, y + vec.y);
}

void Vector2::operator += (Vector2 vec)
{
	x += vec.x;
	y += vec.y;
}

Vector2 Vector2::operator - (Vector2 vec)
{
	return Vector2(x - vec.x, y - vec.y);
}

void Vector2::operator -= (Vector2 vec)
{
	x -= vec.x;
	y -= vec.y;
}

double Vector2::abs()
{
	return sqrt((double)x * (double)x + (double)y * (double)y);
}

Vector2 Vector2::normalized()
{
	if (abs() == 0)
		return Vector2(0, 0);

	return *this / abs();
}

float Vector2::dot(Vector2 vec) // Dot product
{
	return (x * vec.x + y * vec.y);
}

float Vector2::operator * (Vector2 vec) // Dot product
{
	return (x * vec.x + y * vec.y);
}

Vector2 Vector2::operator / (double divisor) // scalar division
{
	return Vector2(x / divisor, y / divisor);
}

void Vector2::set(float initX, float initY)
{
	x = initX;
	y = initY;
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

double Vector3::abs()
{
	return sqrt((double)x * (double)x + (double)y * (double)y + (double)z * (double)z);
}

Vector3 Vector3::normalized()
{
	if (abs() == 0)
		return Vector3(0, 0, 0);

	return *this / abs();
}

float Vector3::dot(Vector3 vec) // Dot product
{
	return (x * vec.x + y * vec.y + z * vec.z);
}

float Vector3::operator * (Vector3 vec) // Dot product
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
