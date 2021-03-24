#ifndef CG_TRANSFORM_H
#define CG_TRANSFORM_H
#include "stdafx.h"
#include "Vector3.h"
#include "Component.h"
CG_BEGIN
class Transform :public Component
{
public:
	Vector3 position;
	Vector3 eulerRotation;
	Vector3 scale = { 1, 1, 1 };

	void Rotate(float x, float y, float z);
	void Rotate(const Vector3 &rotation);
	void RotateAround(const Vector3 &point, const Vector3 &axis, float angle);

};
CG_END
#endif