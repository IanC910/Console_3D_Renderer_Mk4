#ifndef	TRIANGLE_H
#define	TRIANGLE_H

#include "Common.h"
#include "Vertex.h"

class Triangle
{
public:
	Vertex* vertices[3];

	Triangle();
	Triangle(Vertex*, Vertex*, Vertex*);
	~Triangle();

	Vec3 normal();
};

#endif

