#include "stdafx.h"
#include "Script.h"
#include "Transform.h"
CG_BEGIN
class TeapotScript :public Script
{
public:
	TeapotScript(Object *pObj) :Script(pObj){}
	float speed = 3;
	void Update() override
	{
		transform.Rotate(0, speed, 0);
		//transform.RotateAround(Vector3::Zero(),Vector3::Up(),speed);
	}

};
CG_END