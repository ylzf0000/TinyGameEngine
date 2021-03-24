#ifndef CG_VERTEX_H
#define CG_VERTEX_H
#include "stdafx.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Color.h"
CG_BEGIN
class Vertex
{
public:
	Vertex() = default;
	Vertex(const Vector3 &pos)
	{
		x = pos.x;
		y = pos.y;
		z = pos.z;
	}
	Vertex(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	Vector3 GetVector3() const
	{
		return Vector3(x, y, z);
	}
	Vector4 GetVector4() const
	{
		return Vector4(x, y, z, 1.f);
	}
	float x;
	float y;
	float z;
	Vector3 normal;
	ColorF color = 0;
};

class VertexInt
{
public:
	VertexInt() = default;
	VertexInt(const Vector3Int &pos)
	{
		x = pos.x;
		y = pos.y;
		z = pos.z;
	}
	VertexInt(int _x, int _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	Vector3Int GetVector3Int() const
	{
		return { x, y, z };
	}
	int x;
	int y;
	float z;
	ColorF color = 0;
};
CG_END
#endif
