// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件: 
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO:  在此处引用程序需要的其他头文件
#include <cmath>
#include <iostream>

#define CG			::cg::
#define CG_BEGIN	namespace cg {
#define CG_END		}
#define _NOEXCEPT noexcept

CG_BEGIN

extern const float EPSILON;
extern const float pi;
float Pi();
//bool Equal(float a, float b);
float Sin(float angle);
float Cos(float angle);
float Tan(float angle);

template <typename T1, typename T2>
inline bool Equal(T1 a, T2 b)
{
	return a == b;
}

template <>
inline bool Equal(float a, float b)
{
	return abs(a - b) <= EPSILON;
}

enum ColorEnum :COLORREF
{
	Red = 0x00FF0000,
	Green = 0x0000FF00,
	Blue = 0x000000FF,
	White = 0x00FFFFFF,
	Black = 0x00000000,
	Grey = 0x00BEBEBE,
	SeaGreen = 0x0054FF9F,
	Yellow = 0x00FFFF00,
	Turquoise = 0x0000F5FF,
	Chocolate = 0x00FF7F24,
	Magenta4 = 0x008B008B,
};

/*背面剔除模式*/
enum CullingMode
{
	Front,
	Back,
	Non
};

/*渲染模式*/
enum FillMode
{
	Solid,		//面模式
	Point,		//点模式
	WireFrame	//线框模式
};

/*法线显示模式*/
enum NormalMode
{
	Enable,
	Disable
};

struct NormalShow
{
	COLORREF color;
	int length;
	NormalShow(COLORREF c, int len) :color(c), length(len){}
};

/*线性插值*/
template <typename T>
T Lerp(const T &a, const T &b, const T &t)
{
	if (t < 0)
		return a;
	if (t > 1)
		return b;
	return a + (b - a) / t;
}

/*限制范围*/
template <typename T, typename F>
T Clamp(const T &value, const F &min, const F &max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}


/*Bresenham画线法*/
//void DrawLine(int x0, int y0, int x1, int y1, Color color = RGB(255, 0, 0));
//void DrawLine(const Vector2 &a, const Vector2 &b, Color color = RGB(255, 0, 0));
//void DrawLine(int x0, int y0, float z0, int x1, int y1, float z1, Color color);
//void DrawLine(const Vector3 &a, const Vector3 &b, Color color);
//void DrawEdge(int x0, int y0, float z0, int x1, int y1, float z1, Color color);
//void DrawEdge(const Vector3 &a, const Vector3 &b, Color color);

CG_END
