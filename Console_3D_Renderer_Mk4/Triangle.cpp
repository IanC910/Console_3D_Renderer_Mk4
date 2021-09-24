#include "Triangle.h"

Triangle::Triangle()
{
	vertices = new Vertex*[3];

	for (int i = 0; i < 3; i++)
		vertices[i] = nullptr;

	normal.set(0, 0, 0);
}

Triangle::Triangle(Vertex* vertex0, Vertex* vertex1, Vertex* vertex2)
{
	vertices = new Vertex*[3];

	vertices[0] = vertex0;
	vertices[1] = vertex1;
	vertices[2] = vertex2;

	normal = (vertex1->pos - vertex0->pos).cross(vertex2->pos - vertex1->pos);

	normal = normal / normal.abs();
}

Triangle::~Triangle()
{
	for (int v = 0; v < 3; v++)
	{
		vertices[v] = nullptr;
	}

	delete[] vertices;
	vertices = nullptr;
}