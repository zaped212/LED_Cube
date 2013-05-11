#include "Rain.h"

Rain::Rain(Cube8x8x8 *CubeRef, long UpdateDelay, int axis, int Direction)
{
	Cube = CubeRef;
	Delay = UpdateDelay;
	RainDirection = Direction;
	Axis = axis;
}

void Rain::End()
{
}

void Rain::Begin()
{
	Cube->CreateCubeOff();
	StartTime = millis();
}

void Rain::Update()
{
	
	if(millis() > StartTime + Delay)
	{
		StartTime = millis();
		
		if(Axis == Z_Axis) Cube->Shift(Z_Axis,RainDirection);
		else if(Axis == Y_Axis) Cube->Shift(Y_Axis,RainDirection);
		else if(Axis == X_Axis) Cube->Shift(X_Axis,RainDirection);

		//get random number of rain drops to generate 0-4
		int num = random()%4;
		// foreach raindrop randomize a x,y,7 cordinate
		for(int i = 0; i < num; i++)
		{
			rand_x = random()%8;
			rand_y = random()%8;
			if(Axis == Z_Axis)
			{
				if(RainDirection < 0) Cube->SetVoxel(rand_x,rand_y,7,1);
				else Cube->SetVoxel(rand_x,rand_y,0,1);
			}
			else if(Axis == Y_Axis)
			{
				if(RainDirection < 0) Cube->SetVoxel(rand_x,7, rand_y,1);
				else Cube->SetVoxel(rand_x,0,rand_y,1);
			}
			else if(Axis == X_Axis)
			{
				if(RainDirection < 0) Cube->SetVoxel(7,rand_y,rand_x,1);
				else Cube->SetVoxel(0,rand_y,rand_x,1);
			}
		}
	}
}