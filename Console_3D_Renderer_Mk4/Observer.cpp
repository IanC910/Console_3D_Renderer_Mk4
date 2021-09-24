#include "Observer.h"

Observer::Observer()
{
	pos.set(0, 0, 0);
	lineOfSight.set(0, 0, 0);
	vertLookAngle = 0;
	horizLookAngle = 0;
	moveSpeed = 0;
	turnSpeed = 0;
}

Observer::Observer(float initX, float initY, float initZ)
{
	pos.set(initX, initY, initZ);
	vertLookAngle = 0;
	horizLookAngle = 0;
	moveSpeed = 0;
	turnSpeed = 0;
}

void Observer::GetUserInput(double elapsedTime)
{
	Vector3 direction;

	if (GetAsyncKeyState('W')) // Move Forward
	{
		direction = lineOfSight;
		direction.z = 0;
		pos += direction * moveSpeed * elapsedTime / direction.abs();
	}

	if (GetAsyncKeyState('S')) // Move Backward
	{
		direction = lineOfSight;
		direction.z = 0;
		pos += direction * (-moveSpeed) * elapsedTime / direction.abs();
	}

	if (GetAsyncKeyState('A')) // Move Left
	{
		direction.set(-lineOfSight.y, lineOfSight.x, 0); // lineOfSight rotated PI/2 counter clockwise
		pos += direction * moveSpeed * elapsedTime / direction.abs();
	}

	if (GetAsyncKeyState('D')) // Move Right
	{
		direction.set(lineOfSight.y, -lineOfSight.x, 0); // lineOfSight rotated PI/2 clockwise
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

	if (GetAsyncKeyState(VK_UP) && vertLookAngle < PI / 2.0 - PI / 180.0) // Look Up
	{
		vertLookAngle += turnSpeed * elapsedTime;
	}

	if (GetAsyncKeyState(VK_DOWN) && vertLookAngle > -PI / 2.0 + PI / 180.0) // Look Down
	{
		vertLookAngle -= turnSpeed * elapsedTime;
	}

	if (GetAsyncKeyState(VK_LEFT)) // Look left
	{
		horizLookAngle += turnSpeed * elapsedTime;
	}

	if (GetAsyncKeyState(VK_RIGHT)) // Look Right
	{
		horizLookAngle -= turnSpeed * elapsedTime;
	}

	// Update lineOfSight

	lineOfSight.set(cos(horizLookAngle) * cos(vertLookAngle), sin(horizLookAngle) * cos(vertLookAngle), sin(vertLookAngle));
}
