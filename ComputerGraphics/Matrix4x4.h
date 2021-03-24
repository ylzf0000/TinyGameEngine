#ifndef CG_MATRIX4X4_H
#define CG_MATRIX4X4_H
#include "stdafx.h"
#include <initializer_list>
CG_BEGIN
class Vector4;
class Matrix4x4
{
public:
	~Matrix4x4();
	Matrix4x4();
	Matrix4x4(const Matrix4x4 &matrix);
	Matrix4x4(Matrix4x4 &&matrix) _NOEXCEPT;
	Matrix4x4(const std::initializer_list<float> &lst);
	Matrix4x4 &Set(const Matrix4x4 &matrix);
	Matrix4x4 &Set(Matrix4x4 &&matrix) _NOEXCEPT;
	Matrix4x4 &operator =(const Matrix4x4 &matrix);
	Matrix4x4 &operator =(Matrix4x4 &&matrix) _NOEXCEPT;
	Matrix4x4 &operator *=(const Matrix4x4 &matrix);
	Matrix4x4 &operator *=(float n) _NOEXCEPT;
	Matrix4x4 &operator /=(float n);

	float &operator ()(unsigned index) { return data[index]; }
	const float &operator ()(unsigned index) const { return data[index]; }
	float &operator ()(unsigned row, unsigned col) { return data[Index(row, col)]; }
	const float &operator ()(unsigned row, unsigned col) const { return data[Index(row, col)]; }

	friend void swap(Matrix4x4 &left, Matrix4x4 &right);
	friend Matrix4x4 operator *(const Matrix4x4 &left, const Matrix4x4 &right);
	friend Vector4 operator *(const Matrix4x4 &left, const Vector4 &right);
	friend Matrix4x4 operator *(const Matrix4x4 &left, float n);
	friend Matrix4x4 operator /(const Matrix4x4 &left, float n);

	float Determinant() _NOEXCEPT;//行列式
	bool Inverse(Matrix4x4 &inverse) const _NOEXCEPT;
	//Matrix4x4 Inverse(bool &isSuccess);//逆矩阵
	bool IsIdentity();
	Matrix4x4 &Transpose() _NOEXCEPT;//转置矩阵
	Vector4 GetColumn(unsigned i);
	Vector4 GetRow(unsigned i);
	Matrix4x4 &SetZero();
	Matrix4x4 &SetIdentity();
	static Matrix4x4 Zero();
	static Matrix4x4 Identity();//单位矩阵

	Matrix4x4 &Transformation(float xPos, float yPos, float zPos);//平移变换
	Matrix4x4 &RotationX(float angle);
	Matrix4x4 &RotationY(float angle);
	Matrix4x4 &RotationZ(float angle);
	Matrix4x4 &Scaling(float xScale, float yScale, float zScale);

	const static unsigned DATA_COUNT = 16;
	const static unsigned ROW_COUNT = 4;
	const static unsigned COL_COUNT = 4;
private:
	/*以下是三个初等行变换*/

	/*交换矩阵的i行和j行*/
	Matrix4x4 &_SwapLine(unsigned i, unsigned j);
	/*用n乘i行*/
	Matrix4x4 &_ProductLine(float n, unsigned i);
	/*将i行的n倍加到j行*/
	Matrix4x4 &_AddLine(unsigned i, float n, unsigned j);

	unsigned Index(unsigned row, unsigned col) const
	{
		return row*COL_COUNT + col;
	}
	float *data;

};
inline void swap(Matrix4x4 &left, Matrix4x4 &right)
{
	using std::swap;
	swap(left.data, right.data);
}
Matrix4x4 operator *(const Matrix4x4 &left, const Matrix4x4 &right);
Vector4 operator *(const Matrix4x4 &left, const Vector4 &right);
Matrix4x4 operator *(const Matrix4x4 &left, float n);
Matrix4x4 operator /(const Matrix4x4 &left, float n);
CG_END
#endif // CG_MATRIX4X4_H
