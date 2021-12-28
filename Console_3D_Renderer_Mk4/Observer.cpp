#include "Observer.h"

Observer::Observer()
{
	position.set(0, 0, 0);
	phi = PI / 2;
	theta = 0;
}

Observer::Observer(float initX, float initY, float initZ)
{
	position.set(initX, initY, initZ);
	phi = PI / 2;
	theta = 0;
}

Vec3 Observer::pos()
{
	return position;
}

Vec3 Observer::lineOfSight()
{
	return Vec3(
		cos(theta) * sin(phi),
		sin(theta) * sin(phi),
		cos(phi)
	);
}

void Observer::moveForward(double distance)
{
	Vec3 directionOfMovement = lineOfSight();
	directionOfMovement.z = 0;
	position += directionOfMovement / directionOfMovement.abs() * distance;
}

void Observer::moveBackward(double distance)
{
	Vec3 directionOfMovement = lineOfSight();
	directionOfMovement.z = 0;
	position -= directionOfMovement / directionOfMovement.abs() * distance;
}

void Observer::moveRight(double distance)
{
	// lineOfSight rotated PI/2 clockwise
	Vec3 directionOfMovement = Vec3(lineOfSight().y, -lineOfSight().x, 0);
	position += directionOfMovement / directionOfMovement.abs() * distance;
}

void Observer::moveLeft(double distance)
{
	// lineOfSight rotated PI/2 counter clockwise
	Vec3 directionOfMovement = Vec3(-lineOfSight().y, lineOfSight().x, 0).normalized();
	position += directionOfMovement / directionOfMovement.abs() * distance;
}

void Observer::moveUp(double distance)
{
	position.z += distance;
}

void Observer::moveDown(double distance)
{
	position.z -= distance;
}

void Observer::lookUp(double angleRadians)
{
	if(phi > 0)
		phi -= angleRadians;
}

void Observer::lookDown(double angleRadians)
{
	if(phi < PI)
		phi += angleRadians;
}

void Observer::lookRight(double angleRadians)
{
	theta -= angleRadians;
}

void Observer::lookLeft(double angleRadians)
{
	theta += angleRadians;
}