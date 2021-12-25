
#include <math.h>

#include "Vec3.h"


Vec3::Vec3(double initX, double initY, double initZ)
{
	set(initX, initY, initZ);
}

Vec3::Vec3()
{
	set(0, 0, 0);
}

Vec3 Vec3::operator + (Vec3 vec)
{
	return Vec3(x + vec.x, y + vec.y, z + vec.z);
}

void Vec3::operator += (Vec3 vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
}

Vec3 Vec3::operator - (Vec3 vec)
{
	return Vec3(x - vec.x, y - vec.y, z - vec.z);
}

void Vec3::operator -= (Vec3 vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
}

Vec3 Vec3::projOnto(Vec3 vec)
{
	return vec * (dot(vec) / pow(vec.abs(), 2.0));
}

double Vec3::scalarProjOnto(Vec3 vec)
{
	return dot(vec)/vec.abs();
}

double Vec3::abs()
{
	return sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::normalized()
{
	if (abs() == 0)
		return Vec3(0, 0, 0);

	return *this / abs();
}

double Vec3::dot(Vec3 vec)
{
	return (x * vec.x + y * vec.y + z * vec.z);
}

double Vec3::operator * (Vec3 vec)
{
	return (x * vec.x + y * vec.y + z * vec.z);
}

Vec3 Vec3::operator * (double multiplier)
{
	return Vec3(x * multiplier, y * multiplier, z * multiplier);
}

void Vec3::operator *= (double multiplier)
{
	x *= multiplier;
	y *= multiplier;
	z *= multiplier;
}

Vec3 Vec3::operator / (double divisor)
{
	return Vec3(x / divisor, y / divisor, z / divisor);
}

void Vec3::operator /= (double divisor)
{
	x /= divisor;
	y /= divisor;
	z /= divisor;
}

Vec3 Vec3::cross(Vec3 vec)
{
	return Vec3((y * vec.z - z * vec.y), (z * vec.x - x * vec.z), (x * vec.y - y * vec.x));
}

void Vec3::set(double initX, double initY, double initZ)
{
	x = initX;
	y = initY;
	z = initZ;
}

void Vec3::set(Vec3 v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

Vec3 operator * (double multiplier, Vec3 vec)
{
	return vec * multiplier;
}
