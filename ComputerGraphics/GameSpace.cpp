#include "stdafx.h"
#include "GameSpace.h"

cg::GameSpace::~GameSpace()
{
	delete pAmbientLight;
	delete pTeapot;
}

