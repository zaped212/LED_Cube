#include "ToggleRandom.h"

ToggleRandom::ToggleRandom(Cube8x8x8 *CubeRef, long UpdateDelay)
{
	Cube = CubeRef;
	Delay = UpdateDelay;
}

void ToggleRandom::End()
{
}

void ToggleRandom::Begin()
{
	Cube->CreateCubeOff();
	StartTime = millis();
}

void ToggleRandom::Update()
{
	if(millis() > StartTime + Delay)
	{
		StartTime = millis();
		rand_x = random()%8;
		rand_y = random()%8;
		rand_z = random()%8;
		Cube->ToggleVoxel(rand_x,rand_y,rand_z);
	}
}