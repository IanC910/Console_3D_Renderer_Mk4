
#include <math.h>

#include "Vec2.h"


Vec2::Vec2(double initX, double initY)
{
	set(initX, initY);
}

Vec2::Vec2()
{
	set(0, 0);
}

Vec2 Vec2::operator + (Vec2 vec)
{
	return Vec2(x + vec.x, y + vec.y);
}

void Vec2::operator += (Vec2 vec)
{
	x += vec.x;
	y += vec.y;
}

Vec2 Vec2::operator - (Vec2 vec)
{
	return Vec2(x - vec.x, y - vec.y);
}

void Vec2::operator -= (Vec2 vec)
{
	x -= vec.x;
	y -= vec.y;
}

Vec2 Vec2::projOnto(Vec2 vec)
{
	return vec * (dot(vec) / pow(vec.abs(), 2.0));
}

double Vec2::scalarProjOnto(Vec2 vec)
{
	return dot(vec) / vec.abs();
}

double Vec2::abs()
{
	return sqrt(x * x + y * y);
}

Vec2 Vec2::normalized()
{
	if (abs() == 0)
		return Vec2(0, 0);

	return *this / abs();
}

double Vec2::dot(Vec2 vec)
{
	return (x * vec.x + y * vec.y);
}

double Vec2::operator * (Vec2 vec)
{
	return (x * vec.x + y * vec.y);
}

Vec2 Vec2::operator * (double multiplier)
{
	return Vec2(x * multiplier, y * multiplier);
}

void Vec2::operator *= (double multiplier)
{
	x *= multiplier;
	y *= multiplier;
}

Vec2 Vec2::operator / (double divisor)
{
	return Vec2(x / divisor, y / divisor);
}

void Vec2::operator /= (double divisor)
{
	x /= divisor;
	y /= divisor;
}

void Vec2::set(double initX, double initY)
{
	x = initX;
	y = initY;
}

void Vec2::set(Vec2 v)
{
	x = v.x;
	y = v.y;
}


Vec2 operator * (double multiplier, Vec2 vec)
{
	return vec * multiplier;
}