#include "Maize.h"

Maize::Maize(Cube8x8x8 *CubeRef, long UpdateDelay)
{
	Cube = CubeRef;
	Delay = UpdateDelay;
}

void Maize::Begin()
{	
	Cube->CreateCubeOff();
	Cur_x = random()%8;
	Cur_y = random()%8;
	Cur_z = random()%8;

	Cube->SetVoxel(Cur_x,Cur_y,Cur_z,1);

	Reset = !CalculateDirection();
	StartTime = millis();
}

bool Maize::CalculateDirection()
{
	count = 0;
	Dir_x = 0;
	Dir_y = 0;
	Dir_z = 0;
		
	if(Cube->InRange(Cur_x + 1,Cur_y,Cur_z) && Cube->GetVoxel(Cur_x + 1,Cur_y,Cur_z) == 0)
	{
		List[count] = new Voxel(1,0,0);
		count ++;
	}	
	if(Cube->InRange(Cur_x - 1,Cur_y,Cur_z) && Cube->GetVoxel(Cur_x - 1,Cur_y,Cur_z) == 0)
	{
		List[count] = new Voxel(-1,0,0);
		count ++;
	}	
	if(Cube->InRange(Cur_x,Cur_y+1,Cur_z) && Cube->GetVoxel(Cur_x,Cur_y+1,Cur_z) == 0)
	{
		List[count] = new Voxel(0,1,0);
		count ++;
	}	
	if(Cube->InRange(Cur_x,Cur_y-1,Cur_z) && Cube->GetVoxel(Cur_x,Cur_y-1,Cur_z) == 0)
	{
		List[count] = new Voxel(0,-1,0);
		count ++;
	}	
	if(Cube->InRange(Cur_x,Cur_y,Cur_z+1) && Cube->GetVoxel(Cur_x,Cur_y,Cur_z+1) == 0)
	{
		List[count] = new Voxel(0,0,1);
		count ++;
	}	
	if(Cube->InRange(Cur_x,Cur_y,Cur_z-1) && Cube->GetVoxel(Cur_x,Cur_y,Cur_z-1) == 0)
	{
		List[count] = new Voxel(0,0,-1);
		count ++;
	}

	if(count == 0)	return false;

	rand = random()%count;
	Dir_x = List[rand]->Get_X();
	Dir_y = List[rand]->Get_Y();
	Dir_z = List[rand]->Get_Z();
	Length = (random()%5)+2;

	for(int i = 0; i < count; i++)
	{
		delete List[i];
	}
	return true;
}

void Maize::End()
{
}

void Maize::Update()
{
	if(!Reset && millis() > StartTime + Delay)
	{
		StartTime = millis();
		// while not in range, and selected voxel is not currently turned on
		if(Length <= 0 || !Cube->InRange(Cur_x + Dir_x,Cur_y + Dir_y,Cur_z + Dir_z) ||Cube->GetVoxel(Cur_x + Dir_x,Cur_y + Dir_y,Cur_z + Dir_z) == 1)
		{
			Reset = !CalculateDirection();
		}
		Cur_x += Dir_x;
		Cur_y += Dir_y;
		Cur_z += Dir_z;

		Length--;
		Cube->SetVoxel(Cur_x,Cur_y,Cur_z,1);	
	}
	else if(Reset && millis()-(Delay+2000) > StartTime)
	{
		Begin();
	}
}
