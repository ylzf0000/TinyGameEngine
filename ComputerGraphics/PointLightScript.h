#ifndef CG_POINTLIGHTSCRIPT_H
#define CG_POINTLIGHTSCRIPT_H
#include "stdafx.h"
#include "Script.h"
#include "Object.h"
CG_BEGIN
class PointLightScript :public Script
{
public:
	float distance;
	float speed;
	PointLightScript(Object *pObj) :Script(pObj){}
	virtual void Update() override
	{
		transform.RotateAround(Vector3::Zero(), Vector3::Up(), speed);
	}

};
CG_END
#endif // CG_POINTLIGHTSCRIPT_H
