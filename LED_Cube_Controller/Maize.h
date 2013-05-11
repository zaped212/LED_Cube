#pragma once
#define MAIZE_H

#include <Arduino.h>
#include "EffectClass.h"
#include "Cube8x8x8.h"
#include "Voxel.h"

class Maize: public EffectClass
{
public:
	virtual void Update();
	virtual void Begin();
	virtual void End();
	Maize(Cube8x8x8 *CubeRef, long UpdateDelay);
	bool CalculateDirection();
private:
	Cube8x8x8 *Cube;
	long StartTime;
	long Delay;
	int Cur_x, Dir_x;
	int Cur_y, Dir_y;
	int Cur_z, Dir_z;
	int Length;
	int rand;
	bool Reset;
	int count;

	Voxel *List[6];

};