#ifndef CG_VECTOR4_H
#define CG_VECTOR4_H
#include "stdafx.h"
CG_BEGIN
class Vector2;
class Vector3;
class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;

	explicit Vector4(float x = 0.f, float y = 0.f, float z = 0.f, float w = 1.f)
	{
		SetPos(x, y, z, w);
	}

	explicit Vector4(const Vector2 &v2);
	explicit Vector4(const Vector3 &v3);

	Vector4 &Add(const Vector4 &right);
	Vector4 Add(const Vector4 &right) const;
	Vector4 &Subtract(const Vector4 &right);
	Vector4 Subtract(const Vector4 &right) const;
	float DotProduct(const Vector4 &right) const;

	Vector4 &operator +=(const Vector4 &right);
	Vector4 &operator -=(const Vector4 &right);
	float operator *=(const Vector4 &right) const;
	Vector4 &operator *=(float right);
	Vector4 &operator /=(float right);

	Vector4 &operator -();
	Vector4 operator -() const;
	float &operator [](unsigned n);
	float operator [](unsigned n) const;

	friend bool operator ==(const Vector4 &a, const Vector4 &b);
	friend bool operator !=(const Vector4 &a, const Vector4 &b);
	friend Vector4 operator +(const Vector4 &a, const Vector4 &b);
	friend Vector4 operator -(const Vector4 &a, const Vector4 &b);
	friend float operator *(const Vector4 &a, const Vector4 &b);
	friend Vector4 operator *(const Vector4 &a, float d);
	friend Vector4 operator *(float d, const Vector4 &a);
	friend Vector4 operator /(const Vector4 &a, float d);

	Vector3 GetVector3() const;
	Vector4 Normalized() const;
	float Magnitude() const;
	float SqrMagnitude() const;
	float Distance(const Vector4 &right) const;
	static float Distance(const Vector4 &from, const Vector4 &right);

	static Vector4 Zero(){ return Vector4(0.f, 0.f, 0.f, 0.f); }
	static Vector4 One(){ return Vector4(1.f, 1.f, 1.f, 1.f); }

	Vector4 &SetPos(float x, float y, float z = 0.f, float w = 1.f)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
		return *this;
	}

	Vector4 &SetPos(const Vector4 &a)
	{
		return SetPos(a.x, a.y, a.z, a.w);
	}
};
bool operator ==(const Vector4 &a, const Vector4 &b);
bool operator !=(const Vector4 &a, const Vector4 &b);
Vector4 operator +(const Vector4 &a, const Vector4 &b);
Vector4 operator -(const Vector4 &a, const Vector4 &b);
float operator *(const Vector4 &a, const Vector4 &b);
Vector4 operator *(const Vector4 &a, float d);
Vector4 operator *(float d, const Vector4 &a);
Vector4 operator /(const Vector4 &a, float d);
CG_END
#endif 