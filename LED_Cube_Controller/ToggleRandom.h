#pragma once
#define TOGGLERANDOM_H
#include <Arduino.h>
#include "Cube8x8x8.h"
#include "EffectClass.h"

class ToggleRandom:public EffectClass
{
public:
	ToggleRandom(Cube8x8x8 *CubeRef, long UpdateDelay);
	virtual void Begin();
	virtual void End();
	virtual void Update();
private:
	Cube8x8x8 *Cube;
	long Delay;
	long StartTime;
	int rand_x;
	int rand_y;
	int rand_z;
};
