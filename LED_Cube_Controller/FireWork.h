#pragma once

#include <Arduino.h>
#include "Cube8x8x8.h"
#include "EffectClass.h"

typedef enum
{
	Reset,
	Position,
	Fire,
	Bloom,
	Fade
} FireworkState;

class FireWork : public EffectClass
{
public:
	FireWork(Cube8x8x8 *CubeRef, long UpdateDelay);
	~FireWork(void);

	virtual void Update();
	virtual void Begin();
	virtual void End();

private:
	Cube8x8x8 *Cube;
	long Delay;
	long StartTime;
	FireworkState state;

	int DesiredHeight;
	int CurHeight;
	int x;
	int y;

	void CalcFirePosition();
	void CalcFire();
	void CalcBloom();
	void CalcFade();

};

