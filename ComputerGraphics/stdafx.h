// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�: 
#include <windows.h>

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
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

/*�����޳�ģʽ*/
enum CullingMode
{
	Front,
	Back,
	Non
};

/*��Ⱦģʽ*/
enum FillMode
{
	Solid,		//��ģʽ
	Point,		//��ģʽ
	WireFrame	//�߿�ģʽ
};

/*������ʾģʽ*/
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

/*���Բ�ֵ*/
template <typename T>
T Lerp(const T &a, const T &b, const T &t)
{
	if (t < 0)
		return a;
	if (t > 1)
		return b;
	return a + (b - a) / t;
}

/*���Ʒ�Χ*/
template <typename T, typename F>
T Clamp(const T &value, const F &min, const F &max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}


/*Bresenham���߷�*/
//void DrawLine(int x0, int y0, int x1, int y1, Color color = RGB(255, 0, 0));
//void DrawLine(const Vector2 &a, const Vector2 &b, Color color = RGB(255, 0, 0));
//void DrawLine(int x0, int y0, float z0, int x1, int y1, float z1, Color color);
//void DrawLine(const Vector3 &a, const Vector3 &b, Color color);
//void DrawEdge(int x0, int y0, float z0, int x1, int y1, float z1, Color color);
//void DrawEdge(const Vector3 &a, const Vector3 &b, Color color);

CG_END
