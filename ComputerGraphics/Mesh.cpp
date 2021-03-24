#include "stdafx.h"
#include "Mesh.h"

cg::Vector3 cg::Mesh::Triangle::Normal(const std::vector<Vertex> &vertexList) const
{
	int a = indexs[0];
	int b = indexs[1];
	int c = indexs[2];
	const Vector3 &aPos = vertexList[a].GetVector3();
	const Vector3 &bPos = vertexList[b].GetVector3();
	const Vector3 &cPos = vertexList[c].GetVector3();
	return Vector3::Normal(aPos, bPos, cPos);
}

cg::Vector3 cg::Mesh::Triangle::Normal(const std::vector<Vector3> &posList) const
{
	int a = indexs[0];
	int b = indexs[1];
	int c = indexs[2];
	const Vector3 &aPos = posList[a];
	const Vector3 &bPos = posList[b];
	const Vector3 &cPos = posList[c];
	return Vector3::Normal(aPos, bPos, cPos);
}

cg::Mesh::Triangle::Triangle(const std::initializer_list<int> &lst)
{
	int *p = indexs;
	for (int i : lst)
	{
		*p++ = i;
		if (p == std::end(indexs))
			return;
	}
}

cg::Mesh::Triangle::Triangle()
{
	memset(colors, 0, sizeof colors);
}
