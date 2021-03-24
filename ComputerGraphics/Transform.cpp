#include "stdafx.h"
#include "Transform.h"
#include "Matrix4x4.h"
#include "Vector4.h"
void cg::Transform::Rotate(float x, float y, float z)
{
	eulerRotation.x += x;
	eulerRotation.y += y;
	eulerRotation.z += z;
}

void cg::Transform::Rotate(const Vector3 &rotation)
{
	Rotate(rotation.x, rotation.y, rotation.z);
}

void cg::Transform::RotateAround(const Vector3 &point, const Vector3 &axis, float angle)
{
	Vector3 dist = point - position;
	Matrix4x4 tmp;
	Matrix4x4 root = Matrix4x4::Identity();
	//tmp.RotationZ(angle);
	//root = tmp*root;
	tmp.RotationY(angle);
	root = tmp*root;
	//tmp.RotationX(angle);
	//root = tmp*root;
	dist = (root*dist.GetVector4()).GetVector3();
	position = point - dist;
}
