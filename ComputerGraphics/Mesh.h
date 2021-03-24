#ifndef CG_MESH_H
#define CG_MESH_H
#include "stdafx.h"
#include "Vertex.h"
#include "Component.h"
#include "Color.h"
#include "Vector2.h"
#include <vector>
CG_BEGIN
class Mesh:public Component
{
public:
	Mesh(int nVertex = 0, int nTriangle = 0) :vertexList(nVertex), triangleList(nTriangle){}
	struct Triangle
	{
		Triangle();
		Triangle(const std::initializer_list<int> &lst);

		/*�����ε�����������vertexList�е�����*/
		int indexs[3];
		/*�����ε���������ķ�����*/
		Vector3 normal[3];
		/*�����εĶ�����ɫ*/
		ColorF colors[3];
		/*�Ƿ�ɼ�*/
		bool isVisible = true;
		/*����ͼ����*/
		Vector2 text[3];

		Vector3 Normal(const std::vector<Vertex> &vertexList) const;
		Vector3 Normal(const std::vector<Vector3> &posList) const;
	};

	struct Index
	{
		int vert;
		int normal;
		int texture;
	};

	struct Face
	{
		Index indexs[3];
	};

	std::vector<Vertex> vertexList;
	std::vector<Triangle> triangleList;
	std::vector<Vector3> normalList;
	std::vector<Vector2> textureList;
	std::vector<Face> faceList;

};
CG_END
#endif

