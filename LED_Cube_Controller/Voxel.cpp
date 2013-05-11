#include "Voxel.h"

Voxel::Voxel(int x, int y, int z)
{
	X = x;
	Y = y;
	Z = z;
}

int Voxel::Get_X()
{
	return X;
}

int Voxel::Get_Y()
{
	return Y;
}
int Voxel::Get_Z()
{
	return Z;
}