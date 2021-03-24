#include "stdafx.h"
#include <cmath>
#include <stdexcept>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
float cg::Vector2::operator[](unsigned n) const
{
	return (*const_cast<Vector2*>(this))[n];
}

float & cg::Vector2::operator[](unsigned n)
{
	if (n == 0)
		return x;
	if (n == 1)
		return y;
	throw _STD runtime_error("Index is over 1");
}

cg::Vector2 cg::Vector2::operator-() const
{
	return -Vector2(*this);
}

cg::Vector2 & cg::Vector2::operator-()
{
	return SetPos(-x, -y);
}

cg::Vector2 & cg::Vector2::operator/=(float right)
{
	return SetPos(x / right, y / right);
}

cg::Vector2 & cg::Vector2::operator*=(float right)
{
	return SetPos(x*right, y*right);
}

float cg::Vector2::operator*=(const Vector2 &right) const
{
	return DotProduct(right);
}

cg::Vector2 & cg::Vector2::operator-=(const Vector2 &right)
{
	return Subtract(right);
}

cg::Vector2 & cg::Vector2::operator+=(const Vector2 &right)
{
	return Add(right);
}

float cg::Vector2::DotProduct(const Vector2 &right) const
{
	return x*right.x + y*right.y;
}

cg::Vector2 cg::Vector2::Subtract(const Vector2 &right) const
{
	return Vector2(*this).Subtract(right);
}

cg::Vector2 & cg::Vector2::Subtract(const Vector2 &right)
{
	return SetPos(x - right.x, y - right.y);
}

cg::Vector2 cg::Vector2::Add(const Vector2 &right) const
{
	return Vector2(*this).Add(right);
}

cg::Vector2 & cg::Vector2::Add(const Vector2 &right)
{
	return SetPos(x + right.x, y + right.y);
}

float cg::Vector2::Magnitude() const
{
	return sqrt(SqrMagnitude());
}

float cg::Vector2::SqrMagnitude() const
{
	return x*x + y*y;
}

cg::Vector2 cg::Vector2::Normalized() const
{
	float m = Magnitude();
	return Vector2(x / m, y / m);
}

float cg::Vector2::Distance(const Vector2 &right) const
{
	return (*this - right).Magnitude();
}

float cg::Vector2::Distance(const Vector2 &a, const Vector2 &b)
{
	return a.Distance(b);
}

float cg::Vector2::Distance(float x1, float y1, float x2, float y2)
{
	return Vector2(x1, y1).Distance(Vector2(x2, y2));
}

float cg::Vector2::Angle(const Vector2 &from, const Vector2 &to)
{
	return _STD acos(from*to / (from.Magnitude()*to.Magnitude())) * 180 / Pi();
}

cg::Vector2::Vector2(_STD initializer_list<float> lst)
{
	x = y = 0;
	auto it = lst.begin();
	int i = 0;
	for (; it != lst.end(); ++it, ++i)
	{
		if (i == 0)
			x = *it;
		else if (i == 1)
			y = *it;
		else
			break;
	}
}

cg::Vector2::Vector2(const Vector3 &v3)
{
	x = v3.x;
	y = v3.y;
}

cg::Vector2::Vector2(const Vector4 &v4) :Vector2(v4.GetVector3())
{

}

cg::Vector3 cg::Vector2::GetVector3() const
{
	return Vector3(x, y, 0.f);
}

cg::Vector4 cg::Vector2::GetVector4() const
{
	return Vector4(x, y, 0.f, 1.f);
}

cg::Vector2 cg::operator-(const Vector2 &left, const Vector2 &right)
{
	return Vector2(left) -= right;
}

bool cg::operator==(const Vector2 &left, const Vector2 &right)
{
	return Equal(left.x, right.x) &&
		Equal(left.y, right.y);
}

bool cg::operator!=(const Vector2 &left, const Vector2 &right)
{
	return !(left == right);
}

cg::Vector2 cg::operator*(float d, const Vector2 &a)
{
	return Vector2(a) *= d;
}

cg::Vector2 cg::operator*(const Vector2 &a, float d)
{
	return Vector2(a) *= d;
}

float cg::operator*(const Vector2 &a, const Vector2 &b)
{
	return a.DotProduct(b);
}

cg::Vector2 cg::operator/(const Vector2 &a, float d)
{
	return Vector2(a) /= d;
}

cg::Vector2 cg::operator+(const Vector2 &a, const Vector2 &b)
{
	return Vector2(a.x + b.x, a.y + b.y);
}

