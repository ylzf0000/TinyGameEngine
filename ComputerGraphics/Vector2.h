#ifndef CG_VECTOR2_H
#define CG_VECTOR2_H
#include "stdafx.h"
#include <initializer_list>
CG_BEGIN
class Vector3;
class Vector4;
struct Vector2Int
{
	int x;
	int y;
};
class Vector2
{
public:
	float x;
	float y;

	explicit Vector2(float x = 0.f, float y = 0.f)
	{
		SetPos(x, y);
	}
	explicit Vector2(const Vector3 &v3);
	explicit Vector2(const Vector4 &v4);
	Vector3 GetVector3() const;
	Vector4 GetVector4() const;
	Vector2(_STD initializer_list<float> lst);
	Vector2 &Add(const Vector2 &right);
	Vector2 Add(const Vector2 &right) const;
	Vector2 &Subtract(const Vector2 &right);
	Vector2 Subtract(const Vector2 &right) const;
	float DotProduct(const Vector2 &right) const;

	Vector2 &operator +=(const Vector2 &right);
	Vector2 &operator -=(const Vector2 &right);
	float operator *=(const Vector2 &right) const;
	Vector2 &operator *=(float right);
	Vector2 &operator /=(float right);


	Vector2 &operator -();
	Vector2 operator -()const;
	float &operator [](unsigned n);
	float operator [](unsigned n) const;
	friend Vector2 operator -(const Vector2 &left, const Vector2 &right);
	friend bool operator ==(const Vector2 &left, const Vector2 &right);
	friend bool operator !=(const Vector2 &left, const Vector2 &right);
	friend float operator *(const Vector2 &a, const Vector2 &b);
	friend Vector2 operator *(float d, const Vector2 &a);
	friend Vector2 operator *(const Vector2 &a, float d);
	friend Vector2 operator /(const Vector2 &a, float d);
	friend Vector2 operator +(const Vector2 &a, const Vector2 &b);

	float Magnitude() const;
	float SqrMagnitude() const;
	Vector2 Normalized() const;
	float Distance(const Vector2 &right) const;

	static Vector2 Zero(){ return Vector2(); }
	static Vector2 One(){ return Vector2(1.f, 1.f); }
	static Vector2 Right() { return Vector2(1.f, 0.f); }
	static Vector2 Left() { return -Right(); }
	static Vector2 Up() { return Vector2(0.f, 1.f); }
	static Vector2 Down() { return -Up(); }

	static float Angle(const Vector2 &from, const Vector2 &to);
	static float Distance(const Vector2 &a, const Vector2 &b);
	static float Distance(float x1, float y1, float x2, float y2);


	Vector2 &SetPos(float x, float y)
	{
		this->x = x;
		this->y = y;
		return *this;
	}

	Vector2 &SetPos(const Vector2 &right)
	{
		return SetPos(right.x, right.y);
	}
};
Vector2 operator -(const Vector2 &left, const Vector2 &right);
bool operator ==(const Vector2 &left, const Vector2 &right);
bool operator !=(const Vector2 &left, const Vector2 &right);
float operator *(const Vector2 &a, const Vector2 &b);
Vector2 operator *(float d, const Vector2 &a);
Vector2 operator *(const Vector2 &a, float d);
Vector2 operator /(const Vector2 &a, float d);
Vector2 operator +(const Vector2 &a, const Vector2 &b);
CG_END
#endif
