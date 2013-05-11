////RAIN DONE!!!
#pragma once
#define RAIN_H

#include <Arduino.h>
#include "Cube8x8x8.h"
#include "EffectClass.h"

class Rain: public EffectClass
{
public:
	Rain(Cube8x8x8 *CubeRef, long UpdateDelay, int axis, int Direction);
	virtual void Update();
	virtual void Begin();
	virtual void End();
private:
	Cube8x8x8 *Cube;
	long Delay;
	long StartTime;
	int RainDirection;
	int rand_x;
	int rand_y;
	int Axis;
};
