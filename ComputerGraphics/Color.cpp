#include "stdafx.h"
#include "Color.h"
#include "Reflection.h"

//cg::Color::Color(COLORREF colorRef)
//{
//	Set((Value)(colorRef >> 16),
//		(Value)(colorRef >> 8),
//		(Value)(colorRef));
//}
//
//cg::Color::Color(const ColorF &colorF)
//{
//	Set((Value)Clamp(colorF.red, 0, 255),
//		(Value)Clamp(colorF.green, 0, 255),
//		(Value)Clamp(colorF.blue, 0, 255)
//		);
//}
//
//cg::Color::operator COLORREF() const
//{
//	return COLORREF((((COLORREF)red) << 16) | (((COLORREF)green) << 8) | ((COLORREF)blue));
//}
//
//cg::Color & cg::Color::Add(Value r, Value g, Value b)
//{
//	if (red > 255 - r)
//		red = 255;
//	else
//		red += r;
//
//	if (green > 255 - g)
//		green = 255;
//	else
//		green += g;
//
//	if (blue > 255 - b)
//		blue = 255;
//	else
//		blue += b;
//	return *this;
//}
//
//cg::Color & cg::Color::Add(const Color &color)
//{
//	return Add(color.red, color.green, color.blue);
//}
//
//cg::Color & cg::Color::Subtract(Value r, Value g, Value b)
//{
//	if (red < r)
//		red = 0;
//	else
//		red -= r;
//
//	if (green < g)
//		green = 0;
//	else
//		green -= g;
//
//	if (blue < b)
//		blue = 0;
//	else
//		blue -= b;
//	return *this;
//}
//
//cg::Color & cg::Color::Subtract(const Color &color)
//{
//	return Subtract(color.red, color.green, color.blue);
//}
//
//cg::Color & cg::Color::operator+=(const Color &right)
//{
//	return Add(right);
//}
//
//cg::Color & cg::Color::operator-=(const Color &right)
//{
//	return Subtract(right);
//}
//
//cg::Color & cg::Color::Set(Value r, Value g, Value b)
//{
//	red = r;
//	green = g;
//	blue = b;
//	return *this;
//}
//
//cg::Color & cg::Color::Set(const Color &color)
//{
//	return Set(color.red, color.green, color.blue);
//}

cg::ColorF::ColorF(COLORREF colorRef)
{
	Set((Value)(BYTE)(colorRef >> 16),
		(Value)(BYTE)(colorRef >> 8),
		(Value)(BYTE)(colorRef));
}

//cg::ColorF::operator COLORREF() const
//{
//	COLORREF r = red;
//	COLORREF g = green;
//	COLORREF b = blue;
//	COLORREF color = (r << 16) | (g << 8) | b;
//	return color;
//}

cg::ColorF & cg::ColorF::Add(Value r, Value g, Value b)
{
	return Set(red + r, green + g, blue + b);
}

cg::ColorF & cg::ColorF::Add(const ColorF &color)
{
	return Add(color.red, color.green, color.blue);
}

cg::ColorF & cg::ColorF::Subtract(Value r, Value g, Value b)
{
	return Set(red - r, green - g, blue - b);
}

cg::ColorF & cg::ColorF::Subtract(const ColorF &colorF)
{
	return Subtract(colorF.red, colorF.green, colorF.blue);
}

cg::ColorF & cg::ColorF::operator+=(const ColorF &right)
{
	return Add(right);
}

cg::ColorF & cg::ColorF::operator-=(const ColorF &right)
{
	return Subtract(right);
}

cg::ColorF & cg::ColorF::operator*=(Value right)
{
	return Set(red*right, green*right, blue*right);
}

cg::ColorF & cg::ColorF::operator*=(const Reflection &reflection)
{
	return Set(red*reflection.red, green*reflection.green, blue*reflection.blue);
}

cg::ColorF & cg::ColorF::operator/=(Value right)
{
	return Set(red / right, green / right, blue / right);
}

cg::ColorF & cg::ColorF::operator/=(const Reflection &reflection)
{
	return Set(red / reflection.red, green / reflection.green, blue / reflection.blue);
}

cg::ColorF & cg::ColorF::Set(Value r, Value g, Value b)
{
	red = r;
	green = g;
	blue = b;
	return *this;
}

cg::ColorF & cg::ColorF::Set(const ColorF &color)
{
	return Set(color.red, color.green, color.blue);
}

COLORREF cg::ColorF::GetCOLORREF() const
{
	COLORREF r = red;
	COLORREF g = green;
	COLORREF b = blue;
	COLORREF color = (r << 16) | (g << 8) | b;
	return color;
}

//cg::Color cg::operator+(const Color &left, const Color &right)
//{
//	return Color(left) += right;
//}

cg::ColorF cg::operator+(const ColorF &left, const ColorF &right)
{
	return ColorF(left) += right;
}

//cg::Color cg::operator-(const Color &left, const Color &right)
//{
//	return Color(left) -= right;
//}

cg::ColorF cg::operator-(const ColorF &left, const ColorF &right)
{
	return ColorF(left) -= right;
}

cg::ColorF cg::operator*(const ColorF &left, ColorF::Value right)
{
	return ColorF(left) *= right;
}

cg::ColorF cg::operator*(const ColorF &left, const Reflection &reflection)
{
	return ColorF(left) *= reflection;
}

cg::ColorF cg::operator/(const ColorF &left, ColorF::Value right)
{
	return ColorF(left) /= right;
}

cg::ColorF cg::operator/(const ColorF &left, const Reflection &reflection)
{
	return ColorF(left) /= reflection;
}

cg::ColorF cg::Clamp(const ColorF &value, int min, int max)
{
	ColorF color;
	color.red = Clamp(value.red, min, max);
	color.green = Clamp(value.green, min, max);
	color.blue = Clamp(value.blue, min, max);
	return color;
}

std::ostream & cg::operator<<(std::ostream &out, const ColorF &c)
{
	out << "[" << c.red << ", " << c.green << ", " << c.blue << "]";
	return out;
}
