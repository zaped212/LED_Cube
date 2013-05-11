#pragma once
#define ResetDelay 1000
#define RANDOMEFILL_H

#include <Arduino.h>
#include "EffectClass.h"
#include "Cube8x8x8.h"

class RandomFill : public EffectClass
{
public:
	RandomFill(Cube8x8x8 *CubeRef, long UpdateDelay, int state);
	virtual void Begin();
	virtual void Update();
	virtual void End();
private:
	Cube8x8x8 *Cube;
	long Delay;
	long StartTime;
	int Count;
	int State;

	int rand_x;
	int rand_y;
	int rand_z;
};
