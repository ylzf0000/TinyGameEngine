#include "stdafx.h"
#include <stdexcept>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

cg::Vector4::Vector4(const Vector2 &v2)
{
	SetPos(v2.x, v2.y, 1.f, 1.f);
}

cg::Vector4::Vector4(const Vector3 &v3)
{
	SetPos(v3.x, v3.y, v3.z, 1.f);
}

cg::Vector4 & cg::Vector4::Add(const Vector4 &right)
{
	return SetPos(x + right.x, y + right.y, z + right.z, w + right.w);
}

cg::Vector4 cg::Vector4::Add(const Vector4 &right) const
{
	return Vector4(*this).Add(right);
}

cg::Vector4 & cg::Vector4::Subtract(const Vector4 &right)
{
	return SetPos(x - right.x, y - right.y, z - right.z, w - right.w);
}

cg::Vector4 cg::Vector4::Subtract(const Vector4 &right) const
{
	return Vector4(*this).Subtract(right);
}

float cg::Vector4::DotProduct(const Vector4 &right) const
{
	return x*right.x + y*right.y + z*right.z + w*right.w;
}

cg::Vector4 & cg::Vector4::operator+=(const Vector4 &right)
{
	return Add(right);
}

cg::Vector4 & cg::Vector4::operator-=(const Vector4 &right)
{
	return Subtract(right);
}

float cg::Vector4::operator*=(const Vector4 &right) const
{
	return DotProduct(right);
}

cg::Vector4 & cg::Vector4::operator*=(float right)
{
	return SetPos(x*right, y*right, z*right, w*right);
}

cg::Vector4 & cg::Vector4::operator/=(float right)
{
	return SetPos(x / right, y / right, z / right, w / right);
}

cg::Vector4 & cg::Vector4::operator-()
{
	return SetPos(-x, -y, -z, -w);
}

cg::Vector4 cg::Vector4::operator-() const
{
	return -Vector4(*this);
}

float & cg::Vector4::operator[](unsigned n)
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

float cg::Vector4::operator[](unsigned n) const
{
	return (*const_cast<Vector4*>(this))[n];
}

float cg::Vector4::SqrMagnitude() const
{
	return x*x + y*y + z*z + w*w;
}

float cg::Vector4::Magnitude() const
{
	return sqrt(SqrMagnitude());
}

cg::Vector4 cg::Vector4::Normalized() const
{
	float m = Magnitude();
	return Vector4(x / m, y / m, z / m, w / m);
}

float cg::Vector4::Distance(const Vector4 &right) const
{
	return (*this - right).Magnitude();
}

float cg::Vector4::Distance(const Vector4 &from, const Vector4 &right)
{
	return from.Distance(right);
}

cg::Vector3 cg::Vector4::GetVector3() const
{
	if (Equal(w, 0.f))
		throw _STD runtime_error("w is zero");
	return Vector3(x / w, y / w, z / w);
}

bool cg::operator==(const Vector4 &a, const Vector4 &b)
{
	return Equal(a.x, b.x) &&
		Equal(a.y, b.y) &&
		Equal(a.z, b.z) &&
		Equal(a.w, b.w);
}

bool cg::operator!=(const Vector4 &a, const Vector4 &b)
{
	return !(a == b);
}

cg::Vector4 cg::operator+(const Vector4 &a, const Vector4 &b)
{
	return Vector4(a) += b;
}

cg::Vector4 cg::operator-(const Vector4 &a, const Vector4 &b)
{
	return Vector4(a) -= b;
}

float cg::operator*(const Vector4 &a, const Vector4 &b)
{
	return Vector4(a) *= b;
}

cg::Vector4 cg::operator*(const Vector4 &a, float d)
{
	return Vector4(a) *= d;
}

cg::Vector4 cg::operator*(float d, const Vector4 &a)
{
	return Vector4(a) *= d;
}

cg::Vector4 cg::operator/(const Vector4 &a, float d)
{
	return Vector4(a) /= d;
}

