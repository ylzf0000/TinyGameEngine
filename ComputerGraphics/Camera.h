#ifndef CG_CAMERA_H
#define CG_CAMERA_H
#include "stdafx.h"
#include "Object.h"
CG_BEGIN
class Camera :public Object
{
public:
	Camera() = default;
	int width;
	int height;
	float angle;
	float nearPlane;
	float farPlane;
};
CG_END
#endif