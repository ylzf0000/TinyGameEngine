#ifndef CG_VECTOR3_H
#define CG_VECTOR3_H
#include "stdafx.h"
#include <initializer_list>
CG_BEGIN
class Vector2;
class Vector4;
struct Vector3Int
{
	int x;
	int y;
	float z;
};
class Vector3
{
public:
	float x;
	float y;
	float z;

	explicit Vector3(float x = 0.f, float y = 0.f, float z = 0.f)
	{
		SetPos(x, y, z);
	}
	explicit Vector3(const Vector2 &v2);
	Vector4 GetVector4() const;
	Vector2 GetVector2() const;
	Vector3(_STD initializer_list<float> lst);
	Vector3 &operator=(_STD initializer_list<float> lst);
	Vector3 &Add(const Vector3 &right);
	Vector3 Add(const Vector3 &right) const;
	Vector3 &Subtract(const Vector3 &right);
	Vector3 Subtract(const Vector3 &right) const;
	float DotProduct(const Vector3 &right) const;
	Vector3 &CrossProduct(const Vector3 &right);
	Vector3 CrossProduct(const Vector3 &right) const;

	Vector3 &operator +=(const Vector3 &right);
	Vector3 &operator -=(const Vector3 &right);
	float operator *=(const Vector3 &right) const;
	Vector3 &operator *=(float right);
	Vector3 &operator ^=(const Vector3 &right);
	Vector3 &operator /=(float right);
	Vector3 &operator -();
	Vector3 operator -() const;
	float operator [](unsigned n) const;
	float &operator [](unsigned n);

	friend Vector3 operator +(const Vector3 &left, const Vector3 &right);
	friend Vector3 operator -(const Vector3 &left, const Vector3 &right);
	friend float operator *(const Vector3 &left, const Vector3 &right);
	friend Vector3 operator *(const Vector3 &left, float right);
	friend Vector3 operator *(float left, const Vector3 &right);
	friend Vector3 operator ^(const Vector3 &left, const Vector3 &right);
	friend Vector3 operator /(const Vector3 &left, float right);
	friend bool operator ==(const Vector3 &left, const Vector3 &right);
	friend bool operator !=(const Vector3 &left, const Vector3 &right);

	Vector3 Normalized() const;
	float Magnitude() const;
	float SqrMagnitude() const;
	float Distance(const Vector3 &right) const;
	static float Distance(const Vector3 &from, const Vector3 &right);

	static Vector3 Zero(){ return Vector3(); }
	static Vector3 One(){ return Vector3(1.f, 1.f, 1.f); }
	static Vector3 Forward(){ return Vector3(0.f, 0.f, 1.f); }
	static Vector3 Back(){ return -Forward(); }
	static Vector3 Right(){ return Vector3(1.f, 0.f, 0.f); }
	static Vector3 Left(){ return -Right(); }
	static Vector3 Up(){ return Vector3(0.f, 1.f, 0.f); }
	static Vector3 Down(){ return -Up(); }

	/*求出由三个点向量构成的面的法向量*/
	static Vector3 Normal(const Vector3 &a, const Vector3 &b, const Vector3 &c);

	static float Angle(Vector3 from, Vector3 to);

	Vector3 &SetPos(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		return *this;
	}

	Vector3 &SetPos(const Vector3 &right)
	{
		return SetPos(right.x, right.y, right.z);
	}
private:
};

Vector3 operator +(const Vector3 &left, const Vector3 &right);
Vector3 operator -(const Vector3 &left, const Vector3 &right);
float operator *(const Vector3 &left, const Vector3 &right);
Vector3 operator *(const Vector3 &left, float right);
Vector3 operator *(float left, const Vector3 &right);
Vector3 operator ^(const Vector3 &left, const Vector3 &right);
Vector3 operator /(const Vector3 &left, float right);
bool operator ==(const Vector3 &left, const Vector3 &right);
bool operator !=(const Vector3 &left, const Vector3 &right);
CG_END
#endif