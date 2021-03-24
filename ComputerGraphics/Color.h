#ifndef CG_COLOR_H
#define CG_COLOR_H
#include "stdafx.h"
CG_BEGIN
struct Reflection;
class ColorF;
//class Color
//{
//public:
//	using Value = BYTE;
//	Color(Value r, Value g, Value b) :red(r), green(g), blue(b){}
//	Color(COLORREF colorRef);
//	Color(const ColorF &colorF);
//	operator COLORREF() const;
//
//	Color &Add(Value r, Value g, Value b);
//	Color &Add(const Color &color);
//	Color &Subtract(Value r, Value g, Value b);
//	Color &Subtract(const Color &color);
//
//	Color &operator +=(const Color &right);
//	Color &operator -=(const Color &right);
//
//	Color &Set(Value r, Value g, Value b);
//	Color &Set(const Color &color);
//
//	friend Color operator +(const Color &left, const Color &right);
//	friend Color operator -(const Color &left, const Color &right);
//
//	Value red = 0;
//	Value green = 0;
//	Value blue = 0;
//};
//
//Color operator +(const Color &left, const Color &right);
//Color operator -(const Color &left, const Color &right);

class ColorF
{
public:
	using Value = float;
	ColorF() = default;
	ColorF(Value r, Value g, Value b) :red(r), green(g), blue(b){}
	ColorF(COLORREF colorRef);
	COLORREF GetCOLORREF() const;

	ColorF &Add(Value r, Value g, Value b);
	ColorF &Add(const ColorF &colorF);
	ColorF &Subtract(Value r, Value g, Value b);
	ColorF &Subtract(const ColorF &colorF);

	ColorF &operator +=(const ColorF &right);
	ColorF &operator -=(const ColorF &right);
	ColorF &operator *=(Value right);
	ColorF &operator *=(const Reflection &reflection);
	ColorF &operator /=(Value right);
	ColorF &operator /=(const Reflection &reflection);

	ColorF &Set(Value r, Value g, Value b);
	ColorF &Set(const ColorF &color);

	friend ColorF operator +(const ColorF &left, const ColorF &right);
	friend ColorF operator -(const ColorF &left, const ColorF &right);
	friend ColorF operator *(const ColorF &left, Value right);
	friend ColorF operator *(const ColorF &left, const Reflection &reflection);
	friend ColorF operator /(const ColorF &left, Value right);
	friend ColorF operator /(const ColorF &left, const Reflection &reflection);
	friend std::ostream & operator <<(std::ostream &out, const ColorF &c);

	Value red = 0;
	Value green = 0;
	Value blue = 0;
};
ColorF operator +(const ColorF &left, const ColorF &right);
ColorF operator -(const ColorF &left, const ColorF &right);
ColorF operator *(const ColorF &left, ColorF::Value right);
ColorF operator *(const ColorF &left, const Reflection &reflection);
ColorF operator /(const ColorF &left, ColorF::Value right);
ColorF operator /(const ColorF &left, const Reflection &reflection);
std::ostream & operator <<(std::ostream &out, const ColorF &c);
/*ÏÞÖÆ·¶Î§*/
ColorF Clamp(const ColorF &value, int min, int max);
CG_END
#endif

