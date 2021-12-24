#ifndef OBSERVER_H
#define OBSERVER_H

#include "Common/Common.h"


class Observer
{
public:

	Observer();

	Observer(float, float, float);

	Vector3 pos;
	Vector3 lineOfSight; // Line of Sight

	double vertLookAngle;
	double horizLookAngle;
};

#endif
