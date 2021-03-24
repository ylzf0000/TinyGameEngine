#ifndef CG_Vector4T_H
#define CG_Vector4T_H
#include "stdafx.h"
CG_BEGIN
class Vector2;
class Vector3;
template <typename T>
class Vector4T
{
public:
	using Value = T;
	Value x;
	Value y;
	Value z;
	Value w;

	static const unsigned DATA_COUNT = 4;

	Vector4T() = default;

	Vector4T(Value _x, Value _y, Value _z, Value _w)
	{
		SetPos(_x, _y, _z, _w);
	}

	explicit Vector4T(const Vector2 &v2);
	explicit Vector4T(const Vector3 &v3);

	Vector4T &Add(const Vector4T &right)
	{
		return SetPos(x + right.x, y + right.y, z + right.z, w + right.w);
	}

	Vector4T Add(const Vector4T &right) const
	{
		return SetPos(x + right.x, y + right.y, z + right.z, w + right.w);
	}

	Vector4T &Subtract(const Vector4T &right)
	{
		return SetPos(x - right.x, y - right.y, z - right.z, w - right.w);
	}

	Vector4T Subtract(const Vector4T &right) const
	{
		return SetPos(x - right.x, y - right.y, z - right.z, w - right.w);
	}

	Value DotProduct(const Vector4T &right) const
	{
		return x*right.x + y*right.y + z*right.z + w*right.w;
	}

	Vector4T &operator +=(const Vector4T &right)
	{
		return Add(right);
	}

	Vector4T &operator -=(const Vector4T &right)
	{
		return Subtract(right);
	}

	Value operator *=(const Vector4T &right) const
	{
		return DotProduct(right);
	}

	Vector4T &operator *=(Value right)
	{
		return SetPos(x*right, y*right, z*right, w*right);
	}

	Vector4T &operator /=(Value right)
	{
		return SetPos(x / right, y / right, z / right, w / right);
	}

	Vector4T operator -() const
	{
		return SetPos(-x, -y, -z, -w);
	}

	Value &operator [](unsigned n)
	{
		if (n == 0)
			return x;
		if (n == 1)
			return y;
		if (n == 2)
			return z;
		if (n == 3)
			return w;
		throw _STD runtime_error("index is over 3");
	}

	Value operator [](unsigned n) const
	{
		if (n == 0)
			return x;
		if (n == 1)
			return y;
		if (n == 2)
			return z;
		if (n == 3)
			return w;
		throw _STD runtime_error("index is over 3");
	}

	friend bool operator ==(const Vector4T &a, const Vector4T &b)
	{
		return Equal(a.x, b.x) &&
			Equal(a.y, b.y) &&
			Equal(a.z, b.z) &&
			Equal(a.w, b.w);
	}

	friend bool operator !=(const Vector4T &a, const Vector4T &b)
	{
		return !(a == b);
	}

	friend Vector4T operator +(const Vector4T &a, const Vector4T &b)
	{
		return Vector4(a) += b;
	}

	friend Vector4T operator -(const Vector4T &a, const Vector4T &b)
	{
		return Vector4(a) -= b;
	}

	friend Value operator *(const Vector4T &a, const Vector4T &b)
	{
		return Vector4(a) *= b;
	}

	friend Vector4T operator *(const Vector4T &a, Value d)
	{
		return Vector4(a) *= d;
	}

	friend Vector4T operator *(Value d, const Vector4T &a)
	{
		return Vector4(a) *= d;
	}

	friend Vector4T operator /(const Vector4T &a, Value d)
	{
		return Vector4(a) /= d;
	}

	Vector3 GetVector3() const;
	Vector4T Normalized() const;
	Value Magnitude() const;
	Value SqrMagnitude() const;
	Value Distance(const Vector4T &right) const;
	static Value Distance(const Vector4T &from, const Vector4T &right);

	static Vector4T Zero(){ return Vector4T(0.f, 0.f, 0.f, 0.f); }
	static Vector4T One(){ return Vector4T(1.f, 1.f, 1.f, 1.f); }

	Vector4T &SetPos(Value x, Value y, Value z = 0.f, Value w = 1.f)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
		return *this;
	}

	Vector4T &SetPos(const Vector4T &a)
	{
		return SetPos(a.x, a.y, a.z, a.w);
	}
};
CG_END
#endif // CG_Vector4TT_H
