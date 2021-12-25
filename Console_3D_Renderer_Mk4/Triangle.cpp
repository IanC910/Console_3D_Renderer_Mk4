#include "Triangle.h"

Triangle::Triangle() : vertices{ nullptr, nullptr, nullptr } {}

Triangle::Triangle(Vertex* vertex0, Vertex* vertex1, Vertex* vertex2) : vertices{ vertex0, vertex1, vertex2 } {}

Triangle::~Triangle()
{
	for (int v = 0; v < 3; v++)
	{
		vertices[v] = nullptr;
	}
}

Vec3 Triangle::normal()
{
	return (vertices[1]->pos - vertices[0]->pos).cross(vertices[2]->pos - vertices[1]->pos).normalized();
}