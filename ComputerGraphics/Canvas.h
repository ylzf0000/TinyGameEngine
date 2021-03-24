#ifndef CG_CANVAS_H
#define CG_CANVAS_H
#include "stdafx.h"
CG_BEGIN
struct Canvas
{
	LONG x;
	LONG y;
	LONG width;
	LONG height;
	float aspect;//width/height
	LONG Size(){ return width * width; }
};
extern Canvas canvas;
CG_END
#endif // !CG_CANVAS_H
