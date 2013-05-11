#pragma once

#include <Arduino.h>
#include <string.h>

#include "EffectClass.h"
#include "Cube8x8x8.h"
#include "Voxel.h"
#include "CharMatrix.h"

class ScrollingCharDisplay: public EffectClass
{
public:
	ScrollingCharDisplay(Cube8x8x8 *CubeRef, long UpdateDelay, String display);
	~ScrollingCharDisplay(void);

	void UnpackDisplay();

	virtual void Update();
	virtual void Begin();
	virtual void End();

private:
	Cube8x8x8 *Cube;

	// string to be displayed
	String Display;
	int StringSize;
	int StringPos;

	// time between updates
	long StartTime;
	long Delay;

	bool NextChar[8][8];
	int NextPos;
};

