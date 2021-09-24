
#include "Vertex.h"

Vertex::Vertex(void) : pos(Vector3(0, 0, 0)), screenPos(Vector2(0, 0)) {}

Vertex::Vertex(float initX, float initY, float initZ) : pos(Vector3(initX, initY, initZ)), screenPos(Vector2(0, 0)) {}
