
#include <math.h>

#include "Vector2.h"


Vector2::Vector2(double initX, double initY)
{
	set(initX, initY);
}

Vector2::Vector2()
{
	set(0, 0);
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

Vector2 Vector2::projOnto(Vector2 vec)
{
	return vec * (dot(vec) / pow(vec.abs(), 2.0));
}

double Vector2::scalarProjOnto(Vector2 vec)
{
	return dot(vec) / vec.abs();
}

double Vector2::abs()
{
	return sqrt(x * x + y * y);
}

Vector2 Vector2::normalized()
{
	if (abs() == 0)
		return Vector2(0, 0);

	return *this / abs();
}

double Vector2::dot(Vector2 vec)
{
	return (x * vec.x + y * vec.y);
}

double Vector2::operator * (Vector2 vec)
{
	return (x * vec.x + y * vec.y);
}

Vector2 Vector2::operator * (double multiplier)
{
	return Vector2(x * multiplier, y * multiplier);
}

void Vector2::operator *= (double multiplier)
{
	x *= multiplier;
	y *= multiplier;
}

Vector2 Vector2::operator / (double divisor)
{
	return Vector2(x / divisor, y / divisor);
}

void Vector2::operator /= (double divisor)
{
	x /= divisor;
	y /= divisor;
}

void Vector2::set(double initX, double initY)
{
	x = initX;
	y = initY;
}

void Vector2::set(Vector2 v)
{
	x = v.x;
	y = v.y;
}


Vector2 operator * (double multiplier, Vector2 vec)
{
	return vec * multiplier;
}