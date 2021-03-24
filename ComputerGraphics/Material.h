#ifndef CG_MATERIAL_H
#define CG_MATERIAL_H
#include "stdafx.h"
#include "Component.h"
#include "Reflection.h"
CG_BEGIN
class Material :public Component
{
public:
	/*漫反射系数*/
	Reflection diffuse;
	/*环境光反射系数*/
	Reflection ambient;
};
CG_END

#endif // CG_MATERIAL_H
