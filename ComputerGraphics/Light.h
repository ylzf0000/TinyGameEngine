#ifndef CG_LIGHT_H
#define CG_LIGHT_H
#include "stdafx.h"
#include "Object.h"
#include "Color.h"
CG_BEGIN
class Light :public Object
{
public:
	Light() = default;
	Light(const ColorF &clr) :color(clr){}
	ColorF color = ColorEnum::White;
	/*π‚«ø*/
	float intensity;
};
CG_END
#endif // !CG_LIGHT_H
