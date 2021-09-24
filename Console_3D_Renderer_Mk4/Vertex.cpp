#include <math.h>
#include <Windows.h>

#include "Vertex.hpp"
#include "Vector3D.hpp"
#include "Vector2D.hpp"

Vertex::Vertex(void)
{
	pos.set(0, 0, 0);
	appearance = '#';
}

Vertex::Vertex(float tempX, float tempY, float tempZ)
{
	pos.set(tempX, tempY, tempZ);
	appearance = '#';
}

Vertex::Vertex(float tempX, float tempY, float tempZ, char tempApp)
{
	pos.set(tempX, tempY, tempZ);
	appearance = tempApp;
}


// ======================================================================== Observer
Observer::Observer(void)
{
	pos.set(0, 0, 0);
	LOS.set(0, 0, 0);
	vertAngle = 0;
	horizAngle = 0;
}

Observer::Observer(float tempX, float tempY, float tempZ)
{
	pos.set(tempX, tempY, tempZ);
	LOS = pos * (-1.0);
	vertAngle = 0;
	horizAngle = 0;
}

void Observer::GetUserInput(double moveSpeed, double turnSpeed, double elapsedTime)
{
	Vector3D direction;

	if (GetAsyncKeyState('W')) // Move Forward
	{
		direction = LOS;
		direction.z = 0;
		pos += direction * moveSpeed * elapsedTime / direction.abs();
	}

	if (GetAsyncKeyState('S')) // Move Backward
	{
		direction = LOS;
		direction.z = 0;
		pos += direction * (-moveSpeed) * elapsedTime / direction.abs();
	}

	if (GetAsyncKeyState('A')) // Move Left
	{
		direction.set(-LOS.y, LOS.x, 0); // LOS rotated pi/2 counter clockwise
		pos += direction * moveSpeed * elapsedTime / direction.abs();
	}

	if (GetAsyncKeyState('D')) // Move Right
	{
		direction.set(LOS.y, -LOS.x, 0); // LOS rotated pi/2 clockwise
		pos += direction * moveSpeed * elapsedTime / direction.abs();
	}

	if (GetAsyncKeyState(VK_SPACE)) // Move UP
	{
		pos.z += moveSpeed * elapsedTime * 0.8;
	}

	if (GetAsyncKeyState(VK_LCONTROL)) // Move Down
	{
		pos.z -= moveSpeed * elapsedTime * 0.8;
	}

	if (GetAsyncKeyState(VK_UP) && vertAngle < pi / 2.0 - pi / 180.0) // Look Up
	{
		vertAngle += turnSpeed * elapsedTime;
	}

	if (GetAsyncKeyState(VK_DOWN) && vertAngle > -pi / 2.0 + pi / 180.0) // Look Down
	{
		vertAngle -= turnSpeed * elapsedTime;
	}

	if (GetAsyncKeyState(VK_LEFT)) // Look left
	{
		horizAngle += turnSpeed * elapsedTime;
	}

	if (GetAsyncKeyState(VK_RIGHT)) // Look Right
	{
		horizAngle -= turnSpeed * elapsedTime;
	}

	// Update LOS

	LOS.set(cos(horizAngle) * cos(vertAngle), sin(horizAngle) * cos(vertAngle), sin(vertAngle));
}
