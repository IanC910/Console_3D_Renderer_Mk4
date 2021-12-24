
#include <math.h>

#include "Vector3.h"


Vector3::Vector3(double initX, double initY, double initZ)
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
	return vec * (dot(vec) / pow(vec.abs(), 2.0));
}

double Vector3::scalarProjOnto(Vector3 vec)
{
	return dot(vec)/vec.abs();
}

double Vector3::abs()
{
	return sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::normalized()
{
	if (abs() == 0)
		return Vector3(0, 0, 0);

	return *this / abs();
}

double Vector3::dot(Vector3 vec)
{
	return (x * vec.x + y * vec.y + z * vec.z);
}

double Vector3::operator * (Vector3 vec)
{
	return (x * vec.x + y * vec.y + z * vec.z);
}

Vector3 Vector3::operator * (double multiplier)
{
	return Vector3(x * multiplier, y * multiplier, z * multiplier);
}

void Vector3::operator *= (double multiplier)
{
	x *= multiplier;
	y *= multiplier;
	z *= multiplier;
}

Vector3 Vector3::operator / (double divisor)
{
	return Vector3(x / divisor, y / divisor, z / divisor);
}

void Vector3::operator /= (double divisor)
{
	x /= divisor;
	y /= divisor;
	z /= divisor;
}

Vector3 Vector3::cross(Vector3 vec)
{
	return Vector3((y * vec.z - z * vec.y), (z * vec.x - x * vec.z), (x * vec.y - y * vec.x));
}

void Vector3::set(double initX, double initY, double initZ)
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

Vector3 operator * (double multiplier, Vector3 vec)
{
	return vec * multiplier;
}
