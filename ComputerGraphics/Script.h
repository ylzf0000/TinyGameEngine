#ifndef CG_SCRIPT
#define CG_SCRIPT
#include "stdafx.h"
CG_BEGIN
class Object;
class Transform;
class Mesh;
class Script
{
public:
	Script() = delete;
	Script(Object *pObj);
	virtual ~Script() = default;
	virtual void Enable() {}
	virtual void Start() {}
	virtual void Update() {}
protected:
	Object * const pObject;
	Transform &transform;
	Mesh * const pMesh;
};
CG_END
#endif // !CG_SCRIPT
