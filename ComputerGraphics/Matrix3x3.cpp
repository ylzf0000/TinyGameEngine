#include "stdafx.h"
#include "Matrix3x3.h"


cg::Matrix3x3 & cg::Matrix3x3::Set(const Matrix3x3 &matrix)
{
	memcpy(data, matrix.data, sizeof(float)* DATA_COUNT);
	return *this;
}

cg::Matrix3x3::~Matrix3x3()
{
	delete[] data;
}

cg::Matrix3x3::Matrix3x3()
{
	data = new float[DATA_COUNT];
}

cg::Matrix3x3::Matrix3x3(const Matrix3x3 &matrix)
{
	data = new float[DATA_COUNT];
	Set(matrix);
}

cg::Matrix3x3::Matrix3x3(Matrix3x3 &&matrix)
{
	data = matrix.data;
	matrix.data = nullptr;
}



cg::Matrix3x3 & cg::Matrix3x3::operator=(const Matrix3x3 &matrix)
{
	if (this != &matrix)
	{
		Set(matrix);
	}
	return *this;
}

cg::Matrix3x3 & cg::Matrix3x3::operator=(Matrix3x3 &&matrix)
{
	swap(*this, matrix);
	return *this;
}

cg::Matrix3x3 & cg::Matrix3x3::operator*=(const Matrix3x3 &matrix)
{
	Matrix3x3 tmp = Matrix3x3::Zero();
	for (int i = 0; i < ROW_COUNT; ++i)
	for (int k = 0; k < COL_COUNT; ++k)
	for (int j = 0; j < ROW_COUNT; ++j)
	{
		tmp(i, k) += (*this)(i, j)*matrix(j, k);
	}
	data = tmp.data;
	tmp.data = nullptr;
	return *this;
}

cg::Matrix3x3 & cg::Matrix3x3::operator*=(float n)
{
	for (int i = 0; i < DATA_COUNT; ++i)
		data[i] *= n;
	return *this;
}

cg::Matrix3x3 & cg::Matrix3x3::operator/=(float n)
{
	if (Equal(n, 0.f))
		throw std::runtime_error("");
	for (int i = 0; i < DATA_COUNT; ++i)
		data[i] /= n;
	return *this;
}

float & cg::Matrix3x3::operator()(unsigned index)
{
	if (index >= DATA_COUNT)
		throw std::runtime_error("");
	return data[index];
}

float & cg::Matrix3x3::operator()(unsigned row, unsigned col)
{
	return operator()(Index(row, col));
}

const float & cg::Matrix3x3::operator()(unsigned row, unsigned col) const
{
	return operator()(Index(row, col));
}

const float & cg::Matrix3x3::operator()(unsigned index) const
{
	if (index >= DATA_COUNT)
		throw std::runtime_error("");
	return data[index];
}

cg::Matrix3x3 cg::Matrix3x3::Zero()
{
	Matrix3x3 matrix;
	memset(matrix.data, 0, sizeof(float)*DATA_COUNT);
	return matrix;
}

cg::Matrix3x3 cg::Matrix3x3::Identity()
{
	Matrix3x3 matrix;
	matrix(0) = 1;
	matrix(1) = 0;
	matrix(2) = 0;
	matrix(3) = 0;
	matrix(4) = 1;
	matrix(5) = 0;
	matrix(6) = 0;
	matrix(7) = 0;
	matrix(8) = 1;
	return matrix;
}



float cg::Matrix3x3::Determinant() const
{
	const Matrix3x3 &m = *this;
	return m(0, 0)*(m(1, 1)*m(2, 2) - m(1, 2)*m(2, 1)) -
		m(0, 1)*(m(1, 0)*m(2, 2) - m(1, 2)*m(2, 0)) +
		m(0, 2)*(m(1, 0)*m(2, 1) - m(1, 1)*m(2, 0));
}

cg::Matrix3x3 &cg::Matrix3x3::Inverse()
{
	float deter = Determinant();
	if (Equal(deter, 0.f))
	{
		throw std::runtime_error("");
	}
	const Matrix3x3 &t = *this;
	Matrix3x3 m;
	m(0) = t(1, 1)*t(2, 2) - t(1, 2)*t(2, 1);
	m(1) = t(0, 2)*t(2, 1) - t(0, 1)*t(2, 2);
	m(2) = t(0, 1)*t(1, 2) - t(0, 2)*t(1, 1);
	m(3) = t(1, 2)*t(2, 0) - t(1, 0)*t(2, 2);
	m(4) = t(0, 0)*t(2, 2) - t(0, 2)*t(2, 0);
	m(5) = t(0, 2)*t(1, 0) - t(0, 0)*t(1, 2);
	m(6) = t(1, 0)*t(2, 1) - t(1, 1)*t(2, 0);
	m(7) = t(0, 1)*t(2, 0) - t(0, 0)*t(2, 1);
	m(8) = t(0, 0)*t(1, 1) - t(0, 1)*t(1, 0);
	m /= deter;
	data = m.data;
	m.data = nullptr;
	return *this;
}

cg::Matrix3x3 &cg::Matrix3x3::Transpose()
{
	using std::swap;
	for (int i = 0; i < ROW_COUNT; ++i)
	for (int j = 0; j < i; ++j)
	{
		swap((*this)(i, j), (*this)(j, i));
	}
	return *this;
}

bool cg::Matrix3x3::IsIdentity() const
{
	return Equal(data[0], 1) &&
		Equal(data[1], 0) &&
		Equal(data[2], 0) &&
		Equal(data[3], 0) &&
		Equal(data[4], 1) &&
		Equal(data[5], 0) &&
		Equal(data[6], 0) &&
		Equal(data[7], 0) &&
		Equal(data[8], 1);
}

cg::Matrix3x3 cg::operator*(const Matrix3x3 &m0, const Matrix3x3 &m1)
{
	return Matrix3x3(m0) *= m1;
}

cg::Matrix3x3 cg::operator*(const Matrix3x3 &m, float n)
{
	return Matrix3x3(m) *= n;
}

cg::Matrix3x3 cg::operator/(const Matrix3x3 &m, float n)
{
	return Matrix3x3(m) /= n;
}
