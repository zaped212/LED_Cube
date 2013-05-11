#pragma once
#define VOXEL_H

#include <Arduino.h>

class Voxel
{
public:
	Voxel(int x, int y, int z);
	int Get_X();
	int Get_Y();
	int Get_Z();
private:
	int X;
	int Y;
	int Z;
};
