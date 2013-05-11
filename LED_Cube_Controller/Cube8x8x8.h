#pragma once
#define CUBE8X8X8_H
#define X_Axis 0
#define Y_Axis 1
#define Z_Axis 2
#define On	   true
#define Off    false

class Cube8x8x8
{
public:
	Cube8x8x8();
	int GetVoxel(int x, int y, int z);
	void SetVoxel(int x, int y, int z, int state);
	void CreateCubeOff();
	void CreateCubeOn();
	void CreateAxis();
	void CreateWireFrame();
	void CreateCheckerBoard();
	void Shift(int Axis, int Direction);
	void ToggleVoxel(int x, int y, int z);
	bool InRange(int x, int y, int z);
	void SetPlane(int Axis, int slice, int state);
	void RotateShell();

private:
	bool Cube[8][8][8];
};
