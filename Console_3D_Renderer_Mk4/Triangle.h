#ifndef	TRIANGLE_H
#define	TRIANGLE_H

#include "Common/Common.h"
#include "Vertex.h"

class Triangle
{
public:
	Vertex** vertices;
	Vector3 normal;

	Triangle();
	Triangle(Vertex*, Vertex*, Vertex*);
	~Triangle();
};

#endif

