#include "Vector2D.hpp"

void Vector2D::set(float tempX, float tempY)
{
	x = tempX;
	y = tempY;
}

Vector2D::Vector2D(void)
{
	set(0, 0);
}

Vector2D::Vector2D(float tempX, float tempY)
{
	set(tempX, tempY);
}

void Vector2D::operator=(Vector2D A)
{
	x = A.x;
	y = A.y;
}
