#include "stdafx.h"
#include <cstring>
#include <cmath>
#include "Vector4.h"
#include "Matrix4x4.h"

cg::Matrix4x4::~Matrix4x4()
{
	delete[] data;
}

cg::Matrix4x4::Matrix4x4()
{
	data = new float[DATA_COUNT];
}

cg::Matrix4x4::Matrix4x4(const Matrix4x4 &matrix) :Matrix4x4()
{
	Set(matrix);
}

cg::Matrix4x4::Matrix4x4(Matrix4x4 &&matrix) _NOEXCEPT
{
	data = matrix.data;
	matrix.data = nullptr;
}

cg::Matrix4x4::Matrix4x4(const std::initializer_list<float> &lst) :Matrix4x4()
{
	float *p = data;
	float *end = data + DATA_COUNT;
	auto it = lst.begin();
	while (p != end && it != lst.end())
	{
		*p++ = *it++;
	}
}

cg::Matrix4x4 & cg::Matrix4x4::Set(const Matrix4x4 &matrix)
{
	if (this != &matrix)
	{
		memcpy(data, matrix.data, sizeof(float)*DATA_COUNT);
	}
	return *this;
}

cg::Matrix4x4 & cg::Matrix4x4::Set(Matrix4x4 &&matrix) _NOEXCEPT
{
	swap(*this, matrix);
	return *this;
}

cg::Matrix4x4 & cg::Matrix4x4::operator=(const Matrix4x4 &matrix)
{
	if (this != &matrix)
	{
		memcpy(data, matrix.data, sizeof(float)*DATA_COUNT);
	}
	return *this;
}

cg::Matrix4x4 & cg::Matrix4x4::operator=(Matrix4x4 &&matrix) _NOEXCEPT
{
	swap(*this, matrix);
	return *this;
}

cg::Matrix4x4 & cg::Matrix4x4::operator*=(const Matrix4x4 &matrix)
{
	Matrix4x4 tmp = Matrix4x4::Zero();
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

cg::Matrix4x4 & cg::Matrix4x4::operator*=(float n) _NOEXCEPT
{
	for (int i = 0; i < DATA_COUNT; ++i)
	{
		data[i] *= n;
	}
	return *this;
}

cg::Matrix4x4 & cg::Matrix4x4::operator/=(float n)
{
	if (Equal(n, 0.f))
	{
		throw std::runtime_error("");
	}
	for (int i = 0; i < DATA_COUNT; ++i)
	{
		data[i] /= n;
	}
	return *this;
}

float cg::Matrix4x4::Determinant() _NOEXCEPT
{
	return float();
}


bool cg::Matrix4x4::Inverse(Matrix4x4 &inverse) const _NOEXCEPT
{
	inverse = Matrix4x4::Identity();
	Matrix4x4 mat(*this);
	for (int j = 0; j < COL_COUNT; ++j)
	{
		float maxVal = mat(0, j);
		float maxI = 0;
		int zeroCnt = 0;
		for (int i = j; i < ROW_COUNT; ++i)
		{
			float v = abs(mat(i, j));
			if (Equal(v, 0.f))
			{
				++zeroCnt;
				continue;
			}
			if (maxVal < v)
			{
				maxVal = v;
				maxI = i;
			}
		}
		if (zeroCnt == ROW_COUNT)
		{
			return false;
		}
		if (maxI != j)
		{
			mat._SwapLine(maxI, j);
			inverse._SwapLine(maxI, j);
		}
		float tmp;
		tmp = 1.f / mat(j, j);
		mat._ProductLine(tmp, j);
		inverse._ProductLine(tmp, j);
		for (int i = 0; i < ROW_COUNT; ++i)
		{
			if (i != j)
			{
				tmp = -mat(i, j);
				mat._AddLine(j, tmp, i);
				inverse._AddLine(j, tmp, i);
			}
		}
	}
	return true;
}

bool cg::Matrix4x4::IsIdentity()
{
	return Equal(data[0], 1) &&
		Equal(data[1], 0) &&
		Equal(data[2], 0) &&
		Equal(data[3], 0) &&
		Equal(data[4], 0) &&
		Equal(data[5], 1) &&
		Equal(data[6], 0) &&
		Equal(data[7], 0) &&
		Equal(data[8], 0) &&
		Equal(data[9], 0) &&
		Equal(data[10], 1) &&
		Equal(data[11], 0) &&
		Equal(data[12], 0) &&
		Equal(data[13], 0) &&
		Equal(data[14], 0) &&
		Equal(data[15], 1);
}

cg::Matrix4x4 & cg::Matrix4x4::Transpose() _NOEXCEPT
{
	using std::swap;
	for (int i = 0; i < ROW_COUNT; ++i)
	for (int j = 0; j < COL_COUNT; ++j)
		swap((*this)(i, j), (*this)(j, i));
	return *this;
}

cg::Vector4 cg::Matrix4x4::GetColumn(unsigned i)
{
	return Vector4(data[i], data[i + ROW_COUNT], data[i + ROW_COUNT * 2], data[i + ROW_COUNT * 3]);
}

cg::Vector4 cg::Matrix4x4::GetRow(unsigned i)
{
	unsigned j = i*COL_COUNT;
	return Vector4(data[j], data[j + 1], data[j + 2], data[j + 3]);
}

cg::Matrix4x4 & cg::Matrix4x4::SetZero()
{
	memset(data, 0, sizeof(float)*DATA_COUNT);
	return *this;
}

cg::Matrix4x4 & cg::Matrix4x4::SetIdentity()
{
	data[0] = 1;	data[1] = 0;	data[2] = 0;	data[3] = 0;
	data[4] = 0;	data[5] = 1;	data[6] = 0;	data[7] = 0;
	data[8] = 0;	data[9] = 0;	data[10] = 1;	data[11] = 0;
	data[12] = 0;	data[13] = 0;	data[14] = 0;	data[15] = 1;
	return *this;
}

cg::Matrix4x4 cg::Matrix4x4::Zero()
{
	return Matrix4x4().SetZero();
}

cg::Matrix4x4 cg::Matrix4x4::Identity()
{
	return Matrix4x4().SetIdentity();
}

cg::Matrix4x4 & cg::Matrix4x4::Transformation(float xPos, float yPos, float zPos)
{
	data[0] = 1;	data[1] = 0;	data[2] = 0;	data[3] = xPos;
	data[4] = 0;	data[5] = 1;	data[6] = 0;	data[7] = yPos;
	data[8] = 0;	data[9] = 0;	data[10] = 1;	data[11] = zPos;
	data[12] = 0;	data[13] = 0;	data[14] = 0;	data[15] = 1;
	return *this;
}

cg::Matrix4x4 & cg::Matrix4x4::RotationX(float angle)
{
	data[0] = 1; data[1] = 0; data[2] = 0; data[3] = 0;
	data[4] = 0; data[5] = Cos(angle); data[6] = -Sin(angle); data[7] = 0;
	data[8] = 0; data[9] = Sin(angle); data[10] = Cos(angle); data[11] = 0;
	data[12] = 0; data[13] = 0; data[14] = 0; data[15] = 1;
	return *this;
}

cg::Matrix4x4 & cg::Matrix4x4::RotationY(float angle)
{
	data[0] = Cos(angle); data[1] = 0; data[2] = Sin(angle); data[3] = 0;
	data[4] = 0; data[5] = 1; data[6] = 0; data[7] = 0;
	data[8] = -Sin(angle); data[9] = 0; data[10] = Cos(angle); data[11] = 0;
	data[12] = 0; data[13] = 0; data[14] = 0; data[15] = 1;
	return *this;
}

cg::Matrix4x4 & cg::Matrix4x4::RotationZ(float angle)
{
	data[0] = Cos(angle); data[1] = -Sin(angle); data[2] = 0; data[3] = 0;
	data[4] = Sin(angle); data[5] = Cos(angle); data[6] = 0; data[7] = 0;
	data[8] = 0; data[9] = 0; data[10] = 1; data[11] = 0;
	data[12] = 0; data[13] = 0; data[14] = 0; data[15] = 1;
	return *this;
}

cg::Matrix4x4 & cg::Matrix4x4::Scaling(float xScale, float yScale, float zScale)
{
	data[0] = xScale; data[1] = 0; data[2] = 0; data[3] = 0;
	data[4] = 0; data[5] = yScale; data[6] = 0; data[7] = 0;
	data[8] = 0; data[9] = 0; data[10] = zScale; data[11] = 0;
	data[12] = 0; data[13] = 0; data[14] = 0; data[15] = 1;
	return *this;
}

cg::Matrix4x4 & cg::Matrix4x4::_SwapLine(unsigned i, unsigned j)
{
	using std::swap;
	for (int k = 0; k < COL_COUNT; ++k)
	{
		swap((*this)(i, k), (*this)(j, k));
	}
	return *this;
}

cg::Matrix4x4 & cg::Matrix4x4::_ProductLine(float n, unsigned i)
{
	for (int j = 0; j < COL_COUNT; ++j)
	{
		(*this)(i, j) *= n;
	}
	return *this;
}

cg::Matrix4x4 & cg::Matrix4x4::_AddLine(unsigned i, float n, unsigned j)
{
	for (int k = 0; k < COL_COUNT; ++k)
	{
		(*this)(j, k) += (*this)(i, k)*n;
	}
	return *this;
}

cg::Matrix4x4 cg::operator*(const Matrix4x4 &left, const Matrix4x4 &right)
{
	return Matrix4x4(left) *= right;
}

cg::Vector4 cg::operator*(const Matrix4x4 &left, const Vector4 &right)
{
	Vector4 v = Vector4::Zero();
	for (int i = 0; i < 4; ++i)
	for (int k = 0; k < 4; ++k)
	{
		v[i] += left(i, k) * right[k];
	}
	return v;
}

cg::Matrix4x4 cg::operator*(const Matrix4x4 &left, float n)
{
	return Matrix4x4(left) *= n;
}

cg::Matrix4x4 cg::operator/(const Matrix4x4 &left, float n)
{
	return Matrix4x4(left) /= n;
}

