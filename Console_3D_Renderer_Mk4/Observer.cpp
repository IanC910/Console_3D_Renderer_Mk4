#include "Observer.h"

Observer::Observer()
{
	pos.set(0, 0, 0);
	lineOfSight.set(0, 0, 0);
	vertLookAngle = 0;
	horizLookAngle = 0;
}

Observer::Observer(float initX, float initY, float initZ)
{
	pos.set(initX, initY, initZ);
	vertLookAngle = 0;
	horizLookAngle = 0;
}
