#include "stdafx.h"
#include "Script.h"
#include "Object.h"
#include "Mesh.h"
#include "Transform.h"

cg::Script::Script(Object *pObj) :pObject(pObj), transform(pObj->transform), pMesh(pObj->pMesh)
{}
