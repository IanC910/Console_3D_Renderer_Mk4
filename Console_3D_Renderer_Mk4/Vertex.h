
#include "Common.h"

#ifndef VERTEX_H
#define VERTEX_H

class Vertex
{
public:

	Vec3 pos;
	Vec2 screenPos;

	Vertex();
	// Default constructors

	Vertex(float, float, float);
	// Constructor that sets initial position
};

#endif

