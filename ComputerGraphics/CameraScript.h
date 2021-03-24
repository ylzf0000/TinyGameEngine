#ifndef CG_CAMERASCRIPT_H
#define CG_CAMERASCRIPT_H
#include "stdafx.h"
#include "Script.h"
CG_BEGIN
class CameraScript :public Script
{
public:
	CameraScript(Object *pObj) :Script(pObj){}
	virtual void Update() override
	{
		transform.position.z += 0;
	}

};
CG_END

#endif // CG_CAMERASCRIPT_H
