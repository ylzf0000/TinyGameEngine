#ifndef CG_AMBIENTLIGHT_H
#define CG_AMBIENTLIGHT_H
#include "stdafx.h"
#include "Light.h"
CG_BEGIN
class AmbientLight :public Light
{
public:
	AmbientLight() = default;
	AmbientLight(const ColorF &clr) :Light(clr){}
};
CG_END

#endif // CG_AMBIENTLIGHT_H
