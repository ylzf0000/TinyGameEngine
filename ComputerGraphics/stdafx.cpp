// stdafx.cpp : 只包括标准包含文件的源文件
// ComputerGraphics.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO:  在 STDAFX.H 中
// 引用任何所需的附加头文件，而不是在此文件中引用

const float cg::EPSILON = 1e-005f;
const float cg::pi = cg::Pi();

float cg::Pi()
{
	return _STD acos(-1.f);
}

//bool cg::Equal(float a, float b)
//{
//	return abs(a - b) <= EPSILON;
//}

float cg::Sin(float angle)
{
	return sin(angle *  pi / 180);
}

float cg::Cos(float angle)
{
	return cos(angle *  pi / 180);
}

float cg::Tan(float angle)
{
	return tan(angle *  pi / 180);
}

//void cg::DrawLine(int x0, int y0, int x1, int y1, Color color /*= RGB(255, 0, 0)*/)
//{
//	if (y0 == y1)
//	{
//		if (x0 > x1)
//			Swap(x0, x1);
//		for (int x = x0; x <= x1; ++x)
//		{
//			DrawColor(x, y0, color);
//		}
//		return;
//	}
//
//	if (x0 == x1)
//	{
//		if (y0 > y1)
//			Swap(y0, y1);
//		for (int y = y0; y <= y1; ++y)
//		{
//			DrawColor(x0, y, color);
//		}
//		return;
//	}
//	if (x1 - x0 > 0 && y1 - y0 < 0) //位于第4象限
//	{
//		Swap(x0, x1);
//		Swap(y0, y1);
//	}
//	else if (x1 - x0 < 0 && y1 - y0 <= 0) //位于第3象限
//	{
//		Swap(x0, x1);
//		Swap(y0, y1);
//	}
//	int dx, dy, x, y, e;
//	dx = x1 - x0;
//	dy = y1 - y0;
//	x = x0, y = y0;
//	float k = float(dy) / dx;
//
//	if (k >= 0 && k < 1) //斜率[0,1)
//	{
//		e = -dx;
//		for (int i = 0; i <= dx; ++i)
//		{
//			DrawColor(x, y, color);
//			++x;
//			e += 2 * dy;
//			if (e >= 0)
//			{
//				++y;
//				e -= 2 * dx;
//			}
//		}
//	}
//	else if (k >= 1) //斜率[1,+00)
//	{
//		e = -dy;
//		for (int i = 0; i <= dy; ++i)
//		{
//			DrawColor(x, y, color);
//			++y;
//			e += 2 * dx;
//			if (e >= 0)
//			{
//				++x;
//				e -= 2 * dy;
//			}
//		}
//	}
//	else if (k < -1) //斜率(-00,-1)
//	{
//		e = -dy;
//		for (int i = 0; i <= dy; ++i)
//		{
//			DrawColor(x, y, color);
//			++y;
//			e -= 2 * dx;
//			if (e >= 0)
//			{
//				--x;
//				e -= 2 * dy;
//			}
//		}
//	}
//	else if (k >= -1) //斜率[-1,0)
//	{
//		e = dx;
//		for (int i = dx; i <= 0; ++i)
//		{
//			DrawColor(x, y, color);
//			--x;
//			e += 2 * dy;
//			if (e >= 0)
//			{
//				++y;
//				e += 2 * dx;
//			}
//		}
//	}
//}
//
//void cg::DrawLine(const Vector2 &a, const Vector2 &b, Color color /*= RGB(255, 0, 0)*/)
//{
//	DrawLine(a.x, a.y, b.x, b.y, color);
//}
//
//void cg::DrawLine(int x0, int y0, float z0, int x1, int y1, float z1, Color color)
//{
//	if (y0 == y1)
//	{
//		if (x0 > x1)
//			Swap(x0, x1);
//		float d1 = x1 - x0;
//		float _k = (z1 - z0) / d1;
//		float z = z0;
//		for (int x = x0; x <= x1; ++x)
//		{
//			if (SetZIfLess(Index(x, y0), z))
//			{
//				DrawColor(x, y0, color);
//			}
//			z += _k;
//		}
//		return;
//	}
//
//	if (x0 == x1)
//	{
//		if (y0 > y1)
//			Swap(y0, y1);
//		float d1 = y1 - y0;
//		float _k = (z1 - z0) / d1;
//		float z = z0;
//		for (int y = y0; y <= y1; ++y)
//		{
//			if (SetZIfLess(Index(x0, y), z))
//			{
//				DrawColor(x0, y, color);
//			}
//			z += _k;
//		}
//		return;
//	}
//	if (x1 - x0 > 0 && y1 - y0 < 0) //位于第4象限
//	{
//		Swap(x0, x1);
//		Swap(y0, y1);
//	}
//	else if (x1 - x0 < 0 && y1 - y0 <= 0) //位于第3象限
//	{
//		Swap(x0, x1);
//		Swap(y0, y1);
//	}
//	int dx, dy, x, y, e;
//	dx = x1 - x0;
//	dy = y1 - y0;
//	x = x0, y = y0;
//	float k = float(dy) / dx;
//
//	if (k >= 0 && k < 1) //斜率[0,1)
//	{
//		e = -dx;
//		float d1 = dx;
//		float _k = (z1 - z0) / d1;
//		float z = z0;
//		for (int i = 0; i <= dx; ++i)
//		{
//			if (SetZIfLess(Index(x, y), z))
//			{
//				DrawColor(x, y, color);
//			}
//			z += _k;
//
//			++x;
//			e += 2 * dy;
//			if (e >= 0)
//			{
//				++y;
//				e -= 2 * dx;
//			}
//		}
//	}
//	else if (k >= 1) //斜率[1,+00)
//	{
//		e = -dy;
//		float d1 = dy;
//		float _k = (z1 - z0) / d1;
//		float z = z0;
//		for (int i = 0; i <= dy; ++i)
//		{
//			if (SetZIfLess(Index(x, y), z))
//			{
//				DrawColor(x, y, color);
//			}
//			z += _k;
//
//			++y;
//			e += 2 * dx;
//			if (e >= 0)
//			{
//				++x;
//				e -= 2 * dy;
//			}
//		}
//	}
//	else if (k < -1) //斜率(-00,-1)
//	{
//		e = -dy;
//		float d1 = dy;
//		float _k = (z1 - z0) / d1;
//		float z = z0;
//		for (int i = 0; i <= dy; ++i)
//		{
//			if (SetZIfLess(Index(x, y), z))
//			{
//				DrawColor(x, y, color);
//			}
//			z += _k;
//
//			++y;
//			e -= 2 * dx;
//			if (e >= 0)
//			{
//				--x;
//				e -= 2 * dy;
//			}
//		}
//	}
//	else if (k >= -1) //斜率[-1,0)
//	{
//		e = dx;
//		float d1 = dx;
//		float _k = (z1 - z0) / d1;
//		float z = z0;
//		for (int i = dx; i <= 0; ++i)
//		{
//			if (SetZIfLess(Index(x, y), z))
//			{
//				DrawColor(x, y, color);
//			}
//			z += _k;
//
//			--x;
//			e += 2 * dy;
//			if (e >= 0)
//			{
//				++y;
//				e += 2 * dx;
//			}
//		}
//	}
//}
//
//void cg::GamePlay::DrawLine(const Vector3 &a, const Vector3 &b, Color color)
//{
//	DrawLine(a.x, a.y, a.z, b.x, b.y, b.z, color);
//}
