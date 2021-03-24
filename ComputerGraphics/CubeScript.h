#ifndef CG_CUBESCRIPT_H
#define CG_CUBESCRIPT_H
#include "stdafx.h"
#include "Script.h"
CG_BEGIN
class Object;
class CubeScript :public Script
{
public:
	float speed = 1;
	CubeScript(Object *pObj);
	void Start() override;
	void Update() override;
};
CG_END
#endif // CG_CUBESCRIPT_H