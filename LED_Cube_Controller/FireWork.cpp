#include "FireWork.h"

#define MaxRadius 3
#define BloomPositions 30

FireWork::FireWork(Cube8x8x8 *CubeRef, long UpdateDelay)
{
	Cube = CubeRef;
	Delay = UpdateDelay;
}


FireWork::~FireWork(void)
{
}

void FireWork::Begin()
{
	Cube->CreateCubeOff();
	StartTime = millis();
	state = Reset;
}

void FireWork::End()
{
}

void FireWork::Update()
{
	if(millis() > StartTime + Delay)
	{
		StartTime = millis();

		switch(state)
		{
		case Reset:
			Cube->CreateCubeOff();
			state = Position;
			break;

		case Position:
			CalcFirePosition();
			state = Fire;			
			break;

		case Fire:
			if(CurHeight < DesiredHeight)	CalcFire();
			
			if(CurHeight == DesiredHeight)	state = Bloom;
			
			break;

		case Bloom:
			CalcBloom();
			CurHeight = 7;
			state = Fade;
			StartTime = millis();
			break;

		case Fade:
			if(CurHeight >= 0)
			{
				CalcFade();
				CurHeight --;
			}
			else state = Reset;
			break;

		default:
			Cube->CreateCubeOff();
			state = Reset;
			break;
		}
	}
}

void FireWork::CalcFirePosition()
{
	// calculate desired height, between layers 4 and 7
	DesiredHeight = (random()%100)%3 + 4;
	x = (random()%100)%2 + 3;
	y = (random()%100)%2 + 3;
	CurHeight = 0;

	Cube->SetVoxel(x,y,CurHeight,On);
}

void FireWork::CalcFire()
{
	Cube->Shift(Z_Axis, 1);
	CurHeight ++;
}

void FireWork::CalcBloom()
{

	// turn off last fire position
	Cube->SetVoxel(x,y,CurHeight,Off);

	// calc x, y, and z offset to position a bloom
	for( int i = 0; i < BloomPositions; i ++)
	{
		int c_x = x + (random()%100)%((2*MaxRadius)+1) - MaxRadius;
		int c_y = y + (random()%100)%((2*MaxRadius)+1) - MaxRadius;
		int c_z = CurHeight + (random()%100)%((2*MaxRadius)+1) - MaxRadius;

		if(Cube->GetVoxel(c_x, c_y, c_z) == 1) i--;
		else Cube->SetVoxel( c_x, c_y, c_z, On);
	}
}

void FireWork::CalcFade()
{
	Cube->Shift(Z_Axis, -1);
}