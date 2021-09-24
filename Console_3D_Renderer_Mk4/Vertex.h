
#include "Common.h"

#ifndef VERTEX_H
#define VERTEX_H

class Vertex
{
public:

	Vertex();
	// Default constructor

	Vertex(float, float, float);
	// Constructor that sets initial position
	
	// Vector3D and Vector2D have their own setters, so there is no need for setters in this class
	Vector3 pos;
	Vector2 screenPos;
};

#endif

