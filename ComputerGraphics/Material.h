#ifndef CG_MATERIAL_H
#define CG_MATERIAL_H
#include "stdafx.h"
#include "Component.h"
#include "Reflection.h"
CG_BEGIN
class Material :public Component
{
public:
	/*������ϵ��*/
	Reflection diffuse;
	/*�����ⷴ��ϵ��*/
	Reflection ambient;
};
CG_END

#endif // CG_MATERIAL_H
