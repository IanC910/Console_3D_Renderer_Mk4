#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
public:

	Vector2D(void);
	// Default Constructor

	Vector2D(float tempX, float tempY);
	// Constructor which sets x and y

	void operator=(Vector2D A);
	// Assignment operator

	void set(float tempX, float tempY);

	float x;
	float y;
};

#endif

