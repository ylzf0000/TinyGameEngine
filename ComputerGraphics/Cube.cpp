#include "stdafx.h"
#include "Cube.h"

cg::Cube::Cube()
{
	pMesh = new Mesh(8, 12);

	pTexture = new Texture();
	pTexture->LoadMap();
	pMaterial = new Material();
	pMaterial->diffuse = { 0.9f, 0.9f, 0.9f };
	pMaterial->ambient = { 0.1f, 0.1f, 0.1f };

	std::vector<Vertex> &vertexList = pMesh->vertexList;
	vertexList[0] = Vertex{ 0, 0, 0 };
	vertexList[1] = Vertex{ 1, 0, 0 };
	vertexList[2] = Vertex{ 1, 0, 1 };
	vertexList[3] = Vertex{ 0, 0, 1 };
	vertexList[4] = Vertex{ 0, 1, 0 };
	vertexList[5] = Vertex{ 1, 1, 0 };
	vertexList[6] = Vertex{ 1, 1, 1 };
	vertexList[7] = Vertex{ 0, 1, 1 };

	using Triangle = Mesh::Triangle;
	std::vector<Triangle> &triangleList = pMesh->triangleList;

	/*保证依顺序求出的面法向量向外*/
	triangleList[0] = Triangle{ 0, 5, 1 };
	triangleList[1] = Triangle{ 0, 4, 5 };

	triangleList[2] = Triangle{ 2, 6, 3 };
	triangleList[3] = Triangle{ 3, 6, 7 };

	triangleList[4] = Triangle{ 0, 3, 4 };
	triangleList[5] = Triangle{ 3, 7, 4 };

	triangleList[6] = Triangle{ 1, 5, 2 };
	triangleList[7] = Triangle{ 2, 5, 6 };

	triangleList[8] = Triangle{ 0, 1, 2 };
	triangleList[9] = Triangle{ 0, 2, 3 };

	triangleList[10] = Triangle{ 4, 6, 5 };
	triangleList[11] = Triangle{ 4, 7, 6 };

	triangleList[0].text[0] = { 0, 0 };
	triangleList[0].text[1] = { 1, 1 };
	triangleList[0].text[2] = { 1, 0 };

	triangleList[1].text[0] = { 0, 0 };
	triangleList[1].text[1] = { 0, 1 };
	triangleList[1].text[2] = { 1, 1 };

	triangleList[2].text[0] = { 0, 0 };
	triangleList[2].text[1] = { 0, 1 };
	triangleList[2].text[2] = { 1, 0 };

	triangleList[3].text[0] = { 1, 0 };
	triangleList[3].text[1] = { 0, 1 };
	triangleList[3].text[2] = { 1, 1 };

	triangleList[4].text[0] = { 1, 0 };
	triangleList[4].text[1] = { 0, 0 };
	triangleList[4].text[2] = { 1, 1 };

	triangleList[5].text[0] = { 0, 0 };
	triangleList[5].text[1] = { 0, 1 };
	triangleList[5].text[2] = { 1, 1 };

	triangleList[6].text[0] = { 0, 0 };
	triangleList[6].text[1] = { 0, 1 };
	triangleList[6].text[2] = { 1, 0 };

	triangleList[7].text[0] = { 1, 0 };
	triangleList[7].text[1] = { 0, 1 };
	triangleList[7].text[2] = { 1, 1 };

	triangleList[8].text[0] = { 0, 1 };
	triangleList[8].text[1] = { 1, 1 };
	triangleList[8].text[2] = { 1, 0 };

	triangleList[9].text[0] = { 0, 1 };
	triangleList[9].text[1] = { 1, 0 };
	triangleList[9].text[2] = { 0, 0 };

	triangleList[10].text[0] = { 0, 0 };
	triangleList[10].text[1] = { 1, 1 };
	triangleList[10].text[2] = { 0, 1 };

	triangleList[11].text[0] = { 0, 0 };
	triangleList[11].text[1] = { 0, 1 };
	triangleList[11].text[2] = { 1, 1 };
}
