#ifndef OBSERVER_H
#define OBSERVER_H

#include "Common.h"


class Observer
{
public:

	Observer();

	Observer(float, float, float);

	Vec3 pos();
	
	// Returns the unit vector in the direction the observer is facing
	Vec3 lineOfSight();

	// Move methods, all arguments are distance
	void moveForward(double);

	void moveBackward(double);

	void moveRight(double);

	void moveLeft(double);

	void moveUp(double);

	void moveDown(double);

	// Look methods, all arguments are angles in degrees
	void lookUp(double);

	void lookDown(double);

	void lookRight(double);

	void lookLeft(double);

private:

	Vec3 position;
	
	// The look angles follow spherical coordinates convention
	// phi is the vertical angle
	double phi;
	// theta is the horizontal angle
	double theta;
};

#endif
