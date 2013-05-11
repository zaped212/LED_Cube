#pragma once

#include <Arduino.h>
#include <string.h>

#include "EffectClass.h"
#include "Cube8x8x8.h"
#include "Voxel.h"
#include "CharMatrix.h"


class Char_Display: public EffectClass
{
public:
	Char_Display(Cube8x8x8 *CubeRef, long UpdateDelay, int Thickness, String display);
	~Char_Display(void);
	void UnpackDisplay();

	
	virtual void Update();
	virtual void Begin();
	virtual void End();


private:
	Cube8x8x8 *Cube;

	// String to be displayed
	String Display;
	
	// Number of elements in the string
	int StringSize;
	// current position in the string
	int StringPos;

	// time between updates
	long StartTime;
	long Delay;

	// 0-8 How many layers to display the characters
	int thickness;
	int thickness_count;

	// character information to be displayed
	bool NextChar[8][8];
	
	int Axis;
	int Dirrection;

};
