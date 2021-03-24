#include "stdafx.h"
#include "Teapot.h"
#include <string>
#include <sstream>
using namespace std;

cg::Teapot::Teapot() :teapotFile("./teapot.obj")
{
	if (teapotFile.bad())
		return;
	pTexture = new Texture();
	pTexture->LoadMap();
	pMaterial = new Material();
	pMaterial->diffuse = { 0.9f, 0.9f, 0.9f };
	pMaterial->ambient = { 0.1f, 0.1f, 0.1f };
	pMesh = new Mesh();
	auto &vertList = pMesh->vertexList;
	auto &normalList = pMesh->normalList;
	auto &textureList = pMesh->textureList;
	auto &faceList = pMesh->faceList;
	auto &triangleList = pMesh->triangleList;
	string line;
	while (getline(teapotFile, line))
	{
		stringstream ss;
		ss << line;
		string front;
		ss >> front;
		if (front == "v")
		{
			float x, y, z;
			ss >> x >> y >> z;
			vertList.push_back({ x, y, z });
		}
		else if (front == "vn")
		{
			float x, y, z;
			ss >> x >> y >> z;
			normalList.push_back({ x, y, z });
		}
		else if (front == "vt")
		{
			float x, y, z;
			ss >> x >> y >> z;
			textureList.push_back({ x, y });
		}
		else if (front == "f")
		{
			//float vert, normal, texture;
			string sindexs[4];
			ss >> sindexs[0] >> sindexs[1] >> sindexs[2] >> sindexs[3];
			Mesh::Index indexs[4];
			Mesh::Face face;
			for (int i = 0; i < 4; ++i)
			{
				const string &s = sindexs[i];
				Mesh::Index &index = indexs[i];
				if (s == "")
					break;
				int is[3];
				int i1, i2;
				i1 = 0;
				for (int i = 0; i < 3; ++i)
				{
					string tmp;
					i2 = s.find("/", i1);
					tmp = s.substr(i1, i2);
					is[i] = stoi(tmp);
					i1 = i2 + 1;
				}
				index.vert = is[0];
				index.texture = is[1];
				index.normal = is[2];
			}
			face.indexs[0] = indexs[0];
			face.indexs[1] = indexs[1];
			face.indexs[2] = indexs[2];
			faceList.push_back(face);
			if (sindexs[3] != "")
			{
				face.indexs[0] = indexs[2];
				face.indexs[1] = indexs[3];
				face.indexs[2] = indexs[0];
				faceList.push_back(face);
			}
		}
	}
	for (const Mesh::Face &face : faceList)
	{
		triangleList.push_back({ face.indexs[0].vert - 1, face.indexs[1].vert - 1, face.indexs[2].vert - 1 });
		auto &triangle = triangleList.back();

		triangle.text[0] = textureList[face.indexs[0].texture - 1];
		triangle.text[1] = textureList[face.indexs[1].texture - 1];
		triangle.text[2] = textureList[face.indexs[2].texture - 1];

		triangle.normal[0] = normalList[face.indexs[0].normal - 1];
		triangle.normal[1] = normalList[face.indexs[1].normal - 1];
		triangle.normal[2] = normalList[face.indexs[2].normal - 1];
	}

}
