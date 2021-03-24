#include "stdafx.h"
#include <cmath>
#include <stdexcept>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

float & cg::Vector3::operator[](unsigned n)
{
	if (n == 0)
		return x;
	else if (n == 1)
		return y;
	else if (n == 2)
		return z;
	else
	{
		throw _STD runtime_error("The index is over 2");
	}
}

cg::Vector3 cg::Vector3::CrossProduct(const Vector3 &right) const
{
	return Vector3(*this).CrossProduct(right);
}

cg::Vector3 cg::Vector3::Subtract(const Vector3 &right) const
{
	return Vector3(*this).Subtract(right);
}

cg::Vector3 cg::Vector3::Add(const Vector3 &right) const
{
	return Vector3(*this).Add(right);
}

cg::Vector3 cg::Vector3::operator-() const
{
	return -Vector3(*this);
}

float cg::Vector3::Distance(const Vector3 &from, const Vector3 &right)
{
	return from.Distance(right);
}

float cg::Vector3::Distance(const Vector3 &right) const
{
	return ((*this) - right).Magnitude();
}

float cg::Vector3::Angle(Vector3 from, Vector3 to)
{
	return _STD acos(from*to / (from.Magnitude()*to.Magnitude())) * 180 / Pi();
}

float cg::Vector3::operator[](unsigned n) const
{
	return (*const_cast<Vector3*>(this))[n];
}

cg::Vector3 cg::Vector3::Normalized() const
{
	float m = Magnitude();
	return Vector3(x / m, y / m, z / m);
}

float cg::Vector3::Magnitude() const
{
	return sqrt(SqrMagnitude());
}

float cg::Vector3::SqrMagnitude() const
{
	return x*x + y*y + z*z;
}

cg::Vector3 & cg::Vector3::operator-()
{
	return SetPos(-x, -y, -z);
}

cg::Vector3 & cg::Vector3::Add(const Vector3 &right)
{
	return SetPos(x + right.x, y + right.y, z + right.z);
}

cg::Vector3 & cg::Vector3::Subtract(const Vector3 &right)
{
	return SetPos(x - right.x, y - right.y, z - right.z);
}

float cg::Vector3::DotProduct(const Vector3 &right) const
{
	return x*right.x + y*right.y + z*right.z;
}

cg::Vector3 &cg::Vector3::CrossProduct(const Vector3 &right)
{
	return SetPos(Vector3(
		y*right.z - right.y*z,
		right.x*z - x*right.z,
		x*right.y - right.x*y));
}

cg::Vector3 & cg::Vector3::operator+=(const Vector3 &right)
{
	return Add(right);
}

cg::Vector3 & cg::Vector3::operator-=(const Vector3 &right)
{
	return Subtract(right);
}

float cg::Vector3::operator*=(const Vector3 &right) const
{
	return DotProduct(right);
}

cg::Vector3 & cg::Vector3::operator*=(float right)
{
	return SetPos(x*right, y*right, z*right);
}

cg::Vector3 &cg::Vector3::operator^=(const Vector3 &right)
{
	return CrossProduct(right);
}

cg::Vector3 & cg::Vector3::operator/=(float right)
{
	return SetPos(x / right, y / right, z / right);
}

cg::Vector3::Vector3(const Vector2 &v2)
{
	SetPos(v2.x, v2.y, 0.f);
}

cg::Vector3::Vector3(_STD initializer_list<float> lst)
{
	x = y = z = 0;
	auto it = lst.begin();
	int i = 0;
	for (; it != lst.end(); ++it, ++i)
	{
		if (i == 0)
			x = *it;
		else if (i == 1)
			y = *it;
		else if (i == 2)
			z = *it;
		else
			break;
	}
}

cg::Vector3 & cg::Vector3::operator=(_STD initializer_list<float> lst)
{
	auto it = lst.begin();
	int i = 0;
	for (; it != lst.end(); ++it, ++i)
	{
		if (i == 0)
			x = *it;
		else if (i == 1)
			y = *it;
		else if (i == 2)
			z = *it;
		else
			break;
	}
	return *this;
}

cg::Vector3 cg::Vector3::Normal(const Vector3 &a, const Vector3 &b, const Vector3 &c)
{
	return (b - a) ^ (c - b);
}

cg::Vector4 cg::Vector3::GetVector4() const
{
	return Vector4(x, y, z, 1.f);
}

cg::Vector2 cg::Vector3::GetVector2() const
{
	return Vector2(x, y);
}

cg::Vector3 cg::operator+(const Vector3 &left, const Vector3 &right)
{
	return Vector3(left) += right;
}

cg::Vector3 cg::operator-(const Vector3 &left, const Vector3 &right)
{
	return Vector3(left) -= right;
}

float cg::operator*(const Vector3 &left, const Vector3 &right)
{
	return Vector3(left) *= right;
}

cg::Vector3 cg::operator*(const Vector3 &left, float right)
{
	return Vector3(left) *= right;
}

cg::Vector3 cg::operator*(float left, const Vector3 &right)
{
	return Vector3(right) *= left;
}

cg::Vector3 cg::operator^(const Vector3 &left, const Vector3 &right)
{
	return Vector3(left) ^= right;
}

cg::Vector3 cg::operator/(const Vector3 &left, float right)
{
	return Vector3(left) /= right;
}

bool cg::operator==(const Vector3 &left, const Vector3 &right)
{
	return Equal(left.x, right.x) &&
		Equal(left.y, right.y) &&
		Equal(left.z, right.z);
}

bool cg::operator!=(const Vector3 &left, const Vector3 &right)
{
	return !(left == right);
}
