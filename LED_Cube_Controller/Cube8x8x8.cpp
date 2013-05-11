#include "Cube8x8x8.h"
#include <Arduino.h>
#include <avr/interrupt.h>

Cube8x8x8::Cube8x8x8()
{
	CreateCubeOff();
}

int Cube8x8x8::GetVoxel(int x, int y, int z)
{
	if(InRange(x,y,z))	return (int)Cube[x][y][z];
	return 0;
}

void Cube8x8x8::SetVoxel(int x, int y, int z, int state)
{
	if(InRange(x,y,z)) Cube[x][y][z] = (bool)state;
}

void Cube8x8x8::ToggleVoxel(int x, int y, int z)
{
	if(InRange(x,y,z))
	{
		Cube[x][y][z] = !Cube[x][y][z];
	}
}

bool Cube8x8x8::InRange(int x, int y, int z)
{
	return (x >= 0 && x < 8 && y >= 0 && y < 8 && z >= 0 && z < 8);
}

void Cube8x8x8::CreateAxis()
{
  for(int x = 0; x < 8; x++)  Cube[x][0][0] = On;
  for(int y = 0; y < 8; y++)  Cube[0][y][0] = On;
  for(int z = 0; z < 8; z++)  Cube[0][0][z] = On;
}

void Cube8x8x8::CreateCubeOff()
{
 for(int x = 0; x < 8; x++)
  {
	for(int y = 0; y < 8; y++)
	{
	  for(int z = 0; z < 8; z++)
	  {
		Cube[x][y][z] = Off;
	  }
	}
  }
}

void Cube8x8x8::CreateCubeOn()
{
  for(int x = 0; x < 8; x++)
  {
	for(int y = 0; y < 8; y++)
	{
	  for(int z = 0; z < 8; z++)
	  {
		Cube[x][y][z] = On;
	  }
	}
  }
}

void Cube8x8x8::CreateWireFrame()
{
  CreateCubeOff();
  for(int x = 0; x < 8; x++)
  {
	Cube[x][0][0] = On;
	Cube[x][7][0] = On;
	Cube[x][0][7] = On;
	Cube[x][7][7] = On;
  }
  for(int y = 0; y < 8; y++)
  {
	Cube[0][y][0] = On;
	Cube[7][y][0] = On;
	Cube[0][y][7] = On;
	Cube[7][y][7] = On;
  }
  for(int z = 0; z < 8; z++)
  {
	Cube[0][0][z] = On;
	Cube[7][0][z] = On;
	Cube[0][7][z] = On;
	Cube[7][7][z] = On;
  }
}

void Cube8x8x8::CreateCheckerBoard()
{
	CreateCubeOff();
	for(int x = 0; x < 8; x++)
	{
		for(int y = 0; y < 8; y++)
		{
			for(int z = 0; z < 8; z++)
			{
				Cube[x][y][z] = ((x+y)%2 + z%2)%2;
			}
		}
	}
}

void Cube8x8x8::Shift(int Axis, int Direction)
{
	int ii, iii;
	int state;

	for(int i = 0; i < 8; i++)
	{
		if(Direction == -1) ii = i;
		else ii = (7-i);

		for(int x = 0; x < 8; x++)
		{
			for(int y = 0; y < 8; y++)
			{
				if(Direction == -1) iii = ii+1;
				else iii = ii-1;

				if(Axis == Z_Axis)
				{
					state = GetVoxel(x,y,iii);
					SetVoxel(x,y,ii,state);
				}
				else if(Axis == Y_Axis)
				{
					state = GetVoxel(x,iii,y);
					SetVoxel(x,ii,y,state);
				}
				else if(Axis == X_Axis)
				{
					state = GetVoxel(iii,y,x);
					SetVoxel(ii,y,x,state);
				}
			}
		}
	}
	


	int plane = 0;
	if(Direction == -1) plane = 7;
	delay(20);
	SetPlane(Axis,plane,0);   
}

void Cube8x8x8::SetPlane(int Axis, int plane, int State)
{
	if(Axis == X_Axis)
	{
		for(int i = 0; i < 8; i++)
		{
			for(int ii = 0; ii < 8; ii++)
			{
				Cube[plane][i][ii] = (bool)State;
			}
		}
	}
	else if(Axis == Y_Axis)
	{
		for(int i = 0; i < 8; i++)
		{
			for(int ii = 0; ii < 8; ii++)
			{
				Cube[i][plane][ii] = (bool)State;
			}
		}
	}
	else if(Axis == Z_Axis)
	{
		
		for(int i = 0; i < 8; i++)
		{
			for(int ii = 0; ii < 8; ii++)
			{
				Cube[i][ii][plane] = (bool)State;
			}
		}
	}
}

void Cube8x8x8::RotateShell()
{
	// rotate the outer shell around the cube

	// repeat alorithm per row
	for(int z = 0; z < 8; z ++)
	{
		// store initial values
		bool prev = Cube[0][0][z];
		bool temp;

		// shift along front face.
		for(int y = 1; y < 8; y++)
		{
			temp = Cube[0][y][z];
			Cube[0][y][z] = prev;
			prev = temp;
		}

		// shift along left side
		for(int x = 1; x < 8; x++)
		{
			temp = Cube[x][7][z];
			Cube[x][7][z] = prev;
			prev = temp;
		}
		
		// shift along back side
		for(int y = 6; y >= 0; y--)
		{
			temp = Cube[7][y][z];
			Cube[7][y][z] = prev;
			prev = temp;
		}
		
		// shift along right side
		for(int x = 6; x >= 0; x--)
		{
			temp = Cube[x][0][z];
			Cube[x][0][z] = prev;
			prev = temp;
		}
		
	}
}
