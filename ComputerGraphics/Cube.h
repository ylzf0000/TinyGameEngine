#ifndef CG_CUBE_H
#define CG_CUBE_H
#include "stdafx.h"
#include "Object.h"
#include "Vertex.h"
#include "Mesh.h"
#include <map>
CG_BEGIN
class Cube :public Object
{
public:
	Cube();
	virtual ~Cube() override = default;
};
CG_END
#endif