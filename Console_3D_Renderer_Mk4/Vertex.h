
#include "Common/Common.h"

#ifndef VERTEX_H
#define VERTEX_H

class Vertex
{
public:

	Vertex();
	// Default constructor

	Vertex(float, float, float);
	// Constructor that sets initial position
	
	// Vec3 and Vec2 have their own setters, so there is no need for setters in this class
	Vec3 pos;
	Vec2 screenPos;
};

#endif

