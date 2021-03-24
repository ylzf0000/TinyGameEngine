#ifndef CG_MATRIX3X3_H
#define CG_MATRIX3X3_H
#include "stdafx.h"
CG_BEGIN
class Matrix3x3
{
public:
	~Matrix3x3();
	Matrix3x3();
	Matrix3x3(const Matrix3x3 &matrix);
	Matrix3x3(Matrix3x3 &&matrix);
	//Matrix3x3(const initializer_list<float> &lst);
	Matrix3x3 &operator =(const Matrix3x3 &matrix);
	Matrix3x3 &operator =(Matrix3x3 &&matrix);
	Matrix3x3 &operator *=(const Matrix3x3 &matrix);
	Matrix3x3 &operator *=(float n);
	Matrix3x3 &operator /=(float n);
	float &operator ()(unsigned row, unsigned col);
	float &operator ()(unsigned index);
	const float &operator ()(unsigned row, unsigned col) const;
	const float &operator ()(unsigned index) const;
	static Matrix3x3 Zero();
	static Matrix3x3 Identity();//µ•Œªæÿ’Û
	float Determinant() const;
	Matrix3x3 &Inverse();
	bool IsIdentity() const;
	Matrix3x3 &Transpose();
	Matrix3x3 &Set(const Matrix3x3 &matrix);

	friend void swap(Matrix3x3 &left, Matrix3x3 &right);
	friend Matrix3x3 operator *(const Matrix3x3 &m0, const Matrix3x3 &m1);
	friend Matrix3x3 operator *(const Matrix3x3 &m, float n);
	friend Matrix3x3 operator /(const Matrix3x3 &m, float n);

	const static int DATA_COUNT = 9;
	const static int ROW_COUNT = 3;
	const static int COL_COUNT = 3;
private:
	unsigned Index(unsigned row, unsigned col) const
	{
		return row*COL_COUNT + col;
	}
	float *data;
};
inline void swap(Matrix3x3 &left, Matrix3x3 &right)
{
	using std::swap;
	swap(left.data, right.data);
}
Matrix3x3 operator *(const Matrix3x3 &m0, const Matrix3x3 &m1);
Matrix3x3 operator *(const Matrix3x3 &m, float n);
Matrix3x3 operator /(const Matrix3x3 &m, float n);

CG_END

#endif // CG_MATRIX3X3_H
