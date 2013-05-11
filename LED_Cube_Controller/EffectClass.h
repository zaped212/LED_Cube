#pragma once
#define EFFECTCLASS_H

class EffectClass
{
public:
	virtual void Update() = 0;
	virtual void Begin() = 0;
	virtual void End() = 0;
private:

};
