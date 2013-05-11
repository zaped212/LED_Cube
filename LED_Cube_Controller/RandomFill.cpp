#include "RandomFill.h"

RandomFill::RandomFill(Cube8x8x8 *CubeRef, long UpdateDelay, int state)
{
	Cube = CubeRef;
	Delay = UpdateDelay;
	State = state;
}

void RandomFill::End()
{
}

void RandomFill::Begin()
{
	if(State == 1) Cube->CreateCubeOff();
	else Cube->CreateCubeOn();
	Count = 0;
	StartTime = millis();
}

void RandomFill::Update()
{
	if(millis() > StartTime + Delay)
	{
		int currentState;
		if(Count < 512)
		{
			StartTime = millis();
			do
			{
				rand_x = random()%8;
				rand_y = random()%8;
				rand_z = random()%8;
				currentState = Cube->GetVoxel(rand_x,rand_y,rand_z);
				if(currentState != State) break;
			}
			while(1);
			Cube->SetVoxel(rand_x,rand_y,rand_z,State);
		}
		Count ++;
		if(millis() - (Delay+2000) > StartTime) Begin();
	}
}
