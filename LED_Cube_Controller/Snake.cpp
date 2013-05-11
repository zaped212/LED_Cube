#include "Snake.h"

Snake::Snake(Cube8x8x8 *CubeRef, long UpdateDelay, int Length)
{
	Cube = CubeRef;
	Delay = UpdateDelay;
	MaxLength = Length;
}

void Snake::Begin()
{
	size = 0;
	Body = (Voxel**)malloc(sizeof(Voxel*)*MaxLength);
	Cube->CreateCubeOff();
	
	Cur_x = random()%8;
	Cur_y = random()%8;
	Cur_z = random()%8;
	
	AddBody(Cur_x,Cur_y,Cur_z);
	
	Reset = !CalculateDirection();
	StartTime = millis();
}

void Snake::AddBody(int x, int y, int z)
{
	// if cube is already max size, remove the tail
	if(size >= MaxLength)
	{
		Voxel *temp = Body[size%MaxLength];
		int tx = temp->Get_X();
		int ty = temp->Get_Y();
		int tz = temp->Get_Z();
		Cube->SetVoxel(tx,ty,tz,0);
		free(temp); // frees up the tail in memory
	}

	Body[size%MaxLength] =  new Voxel(Cur_x,Cur_y,Cur_z);
	Cube->SetVoxel(Cur_x,Cur_y,Cur_z,1);	
	size ++;
}

bool Snake::CalculateDirection()
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

void Snake::End()
{
	DeleteArray();
}

void Snake::Update()
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
		AddBody(Cur_x,Cur_y,Cur_z);
	}
	else if(Reset && millis()-(Delay+2000) > StartTime)
	{
		DeleteArray();
		Begin();
	}
}

void Snake::DeleteArray()
{
	if(size > MaxLength) size = MaxLength;
	for(int x = 0; x < size; x++)
	{
		free(Body[x]);
	}
	free(Body);
	size = 0;
}

Snake::~Snake()
{
	DeleteArray();
}

