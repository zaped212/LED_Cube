#pragma once
#define SNAKE_H


#include <Arduino.h>
#include "EffectClass.h"
#include "Cube8x8x8.h"
#include "Voxel.h"

class Snake: public EffectClass
{
public:
	virtual void Update();
	virtual void Begin();
	virtual void End();
	Snake(Cube8x8x8 *CubeRef, long UpdateDelay, int Length);
	~Snake();
	//Snake(Cube8x8x8 *CubeRed, long UpdateDelay, int StartLength, bool Grow, long GrowDelay);
	bool CalculateDirection();
	void AddBody(int x, int y, int z);
	void DeleteArray();
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
	int MaxLength;
	Voxel *List[6];

	Voxel **Body;
	//Voxel *Body[40];
	long size;
	

};