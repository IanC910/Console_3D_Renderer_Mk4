#include <math.h>
#include "Vector3D.hpp"

Vector3D::Vector3D(float tempX, float tempY, float tempZ)
{
	set(tempX, tempY, tempZ);
}

Vector3D::Vector3D(void)
{
	set(0, 0, 0);
}

// Vector Operators ===================================
Vector3D Vector3D::operator+(Vector3D A)
{
	return Vector3D(x + A.x, y + A.y, z + A.z);
}

void Vector3D::operator+=(Vector3D A)
{
	x += A.x;
	y += A.y;
	z += A.z;
}


Vector3D Vector3D::operator-(Vector3D A)
{
	return Vector3D(x - A.x, y - A.y, z - A.z);
}

void Vector3D::operator-=(Vector3D A)
{
	x -= A.x;
	y -= A.y;
	z -= A.z;
}


Vector3D Vector3D::projOnto(Vector3D A)
{
	return A * (float)((double)dot(A) / pow((double)A.abs(), 2.0));
}


float Vector3D::scalarProjOnto(Vector3D A)
{
	return dot(A)/A.abs();
}


float Vector3D::abs(void)
{
	return (float)sqrt((double)x * (double)x + (double)y * (double)y + (double)z * (double)z);
}


float Vector3D::dot(Vector3D A) // Dot product
{
	return (x * A.x + y * A.y + z * A.z);
}


float Vector3D::operator*(Vector3D A) // Also Dot product
{
	return (x * A.x + y * A.y + z * A.z);
}


Vector3D Vector3D::operator*(float a) // scalar multiplication
{
	return Vector3D(x * a, y * a, z * a);
}

Vector3D Vector3D::operator/(float a) // scalar division
{
	return Vector3D(x / a, y / a, z / a);
}


Vector3D Vector3D::cross(Vector3D A)
{
	return Vector3D((y * A.z - z * A.y), (z * A.x - x * A.z), (x * A.y - y * A.x));
}


void Vector3D::set(float tempX, float tempY, float tempZ)
{
	x = tempX;
	y = tempY;
	z = tempZ;
}

void Vector3D::set(Vector3D v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}
