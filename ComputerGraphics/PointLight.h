#ifndef CG_POINTLIGHT_H
#define CG_POINTLIGHT_H
#include "stdafx.h"
#include "Light.h"
CG_BEGIN
class PointLight :public Light
{
public:
	PointLight() = default;
	PointLight(const ColorF &clr) :Light(clr){}
};
CG_END
#endif // !CG_POINTLIGHT_H
