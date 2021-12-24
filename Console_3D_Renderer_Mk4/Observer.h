#ifndef OBSERVER_H
#define OBSERVER_H

#include "Common/Common.h"


class Observer
{
public:

	Observer();

	Observer(float, float, float);

	Vec3 pos;
	Vec3 lineOfSight; // Line of Sight

	double vertLookAngle;
	double horizLookAngle;
};

#endif
