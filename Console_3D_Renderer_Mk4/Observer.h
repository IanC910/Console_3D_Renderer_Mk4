#ifndef OBSERVER_H
#define OBSERVER_H

#include "Common/Common.h"


class Observer
{
public:
	Observer();

	Observer(float, float, float);

	void GetUserInput(double);
	// Takes input from keyboard to move observer around

	Vector3 pos;
	Vector3 lineOfSight; // Line of Sight

	double vertLookAngle;
	double horizLookAngle;

	double moveSpeed;
	double turnSpeed;

};

#endif
