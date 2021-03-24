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

		/*三角形的三个顶点在vertexList中的索引*/
		int indexs[3];
		/*三角形的三个顶点的法向量*/
		Vector3 normal[3];
		/*三角形的顶点颜色*/
		ColorF colors[3];
		/*是否可见*/
		bool isVisible = true;
		/*纹理图坐标*/
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

