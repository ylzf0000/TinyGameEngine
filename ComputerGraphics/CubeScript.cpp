#include "stdafx.h"
#include "CubeScript.h"
#include "Transform.h"
cg::CubeScript::CubeScript(Object *pObj):Script(pObj)
{

}

void cg::CubeScript::Start()
{

}

void cg::CubeScript::Update()
{
	transform.Rotate(0, speed, 0);
}
