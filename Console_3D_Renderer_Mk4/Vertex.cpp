
#include "Vertex.h"

Vertex::Vertex(void) : pos(Vec3(0, 0, 0)), screenPos(Vec2(0, 0)) {}

Vertex::Vertex(float initX, float initY, float initZ) : pos(Vec3(initX, initY, initZ)), screenPos(Vec2(0, 0)) {}
