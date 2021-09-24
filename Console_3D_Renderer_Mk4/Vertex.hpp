#include <math.h>

#ifndef PI
#define PI

const double pi = 2 * acos(0);

#endif


#ifndef VERTEX_H
#define VERTEX_H

#include "Vector3D.hpp"
#include "Vector2D.hpp"

class Vertex
{
public:

	Vertex();
	// Default constructor

	Vertex(float tempX, float tempY, float tempZ);
	// Constructor that sets Vector3D pos

	Vertex(float tempX, float tempY, float tempZ, char tempApp);
	// Constructor that sets Vector3D pos and appearance to char tempApp
	
	// Vector3D and Vector2D have their own setters, so there is no need for setters in this class
	Vector3D pos;
	Vector2D screenPos;
	char appearance;
};


// ======================================================================== class Observer
class Observer : public Vertex
{
public:
	Observer(void);

	Observer(float tempX, float tempY, float tempZ);

	void GetUserInput(double moveSpeed, double turnSpeed, double elapsedTime);
	// Takes input from keyboard to move observer around

	Vector3D LOS; // Line of Sight (initially -1 * pos)

	float vertAngle;
	float horizAngle;

	// Note: Doesn't use Vector2D screenPos
};

#endif

