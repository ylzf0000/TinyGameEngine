#pragma warning(disable:4996)
#include "stdafx.h"
#include "resource.h"
#include "GamePlay.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Log.h"
#include "Time.h"
#include "Cube.h"
#include "CubeScript.h"
#include "Teapot.h"
#include "PointLightScript.h"
#include "TeapotScript.h"
#include "PointLight.h"
#include "Material.h"
#include "Canvas.h"
#include "CameraScript.h"
#include "Color.h"
#include <ctime>
#include <vector>
#include <map>
#include <unordered_map>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <functional>
#include <memory>
using std::map;
using std::vector;
using std::string;
using std::stringstream;
using std::pair;
using std::shared_ptr;
using std::tuple;
using std::function;
using std::runtime_error;
using std::unordered_map;
using std::get;
using std::sort;
using std::make_pair;
using std::make_shared;
using std::max;
using std::min;
using std::getline;
using std::hex;

//using cg::Color;

//#define DEBUG_LOG

cg::GamePlay::GamePlay(HWND _hWnd)
{
	this->hWnd = _hWnd;
	InitCanvas();
	InitGame();
}

cg::GamePlay::~GamePlay()
{
	delete gs;
	delete colorCache;
	delete zCache;
}

void cg::GamePlay::Render()
{
	hdc = GetDC(hWnd);
	//ShowBitMap();
	StretchDIBits(hdc, canvas.x, canvas.y, canvas.width, canvas.height, 0, 0, canvas.width, canvas.height, colorCache, (const BITMAPINFO*)&bi, DIB_RGB_COLORS, SRCCOPY);
	DrawFPS();

	ReleaseDC(hWnd, hdc);

}

void cg::GamePlay::Tick()
{
	Time::SetDeltaTime();
	if (!isActive)
		return;

	/*检测画布大小是否发生变化*/
	Refresh();

	InitCache();
	if (normalMode == NormalMode::Enable)
	{
		gs->lineList.clear();
	}
	

	/*执行脚本的Update()函数*/
	for (auto &pLight : gs->lightList)
	{
		if (pLight->isActive)
		{
			for (auto &pSc : pLight->scripts)
			{
				pSc->Update();
			}
		}
	}
	for (auto &pSc : gs->camera.scripts)
	{
		pSc->Update();
	}
	for (auto &pObj : gs->objectList)
	{
		if (pObj->isActive)
		{
			for (auto &pSc : pObj->scripts)
			{
				pSc->Update();
			}
		}
	}
	switch (fillMode)
	{
	case cg::Solid:
		FillSolid();
		break;
		//case cg::Point:
		//	break;
	case cg::WireFrame:
		FillWireFrame();
		break;
	default:
		break;
	}

}

void cg::GamePlay::DoFrame()
{
	//time_t begin = clock();
	Tick();
	Render();
	//	time_t end = clock();
	//	time_t delta = difftime(end, begin);
	//#define LOCK_FPS
	//#ifdef LOCK_FPS
	//	if (delta <= 15)
	//		Sleep(15 - delta);
	//#endif // LOCK_FPS
}

void cg::GamePlay::InitCanvas()
{
	/*设置画布大小*/
	SetCanvas();
	/*设置BITMAPV4HEADER*/
	SetBITMAPV4HEADER();
	/*为Cache分配空间*/
	AllocateCache();
}

void cg::GamePlay::InitGame()
{
	gs = new GameSpace();
	Time::SetDeltaTime();
	Camera &camera = gs->camera;
	SetCamera(camera);
	shared_ptr<CameraScript> scriptCamera(make_shared<CameraScript>(&camera));
	camera.scripts.push_back(scriptCamera);
	camera.transform.position = { 0, 0, -500 };

	gs->pAmbientLight = new AmbientLight(ColorEnum::White);

	gs->objectList.push_back(make_shared<Cube>());
	Object &cube = *((gs->objectList).back());
	cube.isActive = false;
	cube.transform.position = { -100, -50, -200 };
	cube.transform.scale = { 100, 100, 100 };
	cube.transform.eulerRotation = { 0, 0, 0 };
	shared_ptr<CubeScript> cubeScript(make_shared<CubeScript>(&cube));
	cubeScript->speed = 1;
	cube.scripts.push_back(cubeScript);

	gs->objectList.push_back(make_shared<Cube>());
	Object &cube2 = *((gs->objectList).back());
	cube2.isActive = true;
	cube2.pTexture->isActive = true;
	cube2.transform.position = { -200, 0, -100 };
	cube2.transform.scale = { 100, 100, 100 };
	cube2.transform.eulerRotation = { 0, 0, 0 };
	shared_ptr<CubeScript> cubeScript2(make_shared<CubeScript>(&cube2));
	cubeScript2->speed = -1;
	cube2.scripts.push_back(cubeScript2);

	gs->objectList.push_back(make_shared<Teapot>());
	Object &teapot = *((gs->objectList).back());
	teapot.pTexture->isActive = true;
	teapot.transform.position = { 100, 0, 0 };
	teapot.transform.scale = { 100, 100, 100 };
	teapot.transform.eulerRotation = { 0, 0, 0 };
	shared_ptr<TeapotScript> teapotScript(make_shared<TeapotScript>(&teapot));
	teapotScript->speed = 1;
	teapot.scripts.push_back(teapotScript);

	gs->lightList.push_back(make_shared<PointLight>());
	Light &pointLight = *((gs->lightList).back());
	pointLight.transform.position = camera.transform.position;
	pointLight.color = ColorEnum::White;
	shared_ptr<PointLightScript> pointLightScript(make_shared<PointLightScript>(&pointLight));
	pointLightScript->speed = 0;
	pointLight.scripts.push_back(pointLightScript);

	//gs->lightList.push_back(make_shared<PointLight>());
	//Light &pointLight2 = *((gs->lightList).back());
	//pointLight2.transform.position = Vector3{ 0, 500, 1500 };
	//pointLight2.color = ColorEnum::White;



}

void cg::GamePlay::MakeWorldMatrix(Matrix4x4 &matrix, const Transform &transform)
{
	matrix.SetIdentity();
	Matrix4x4 tmp;
	tmp.Scaling(transform.scale.x, transform.scale.y, transform.scale.z);
	matrix = tmp*matrix;
	tmp.RotationZ(transform.eulerRotation.z);
	matrix = tmp*matrix;
	tmp.RotationY(transform.eulerRotation.y);
	matrix = tmp*matrix;
	tmp.RotationX(transform.eulerRotation.x);
	matrix = tmp*matrix;
	tmp.Transformation(transform.position.x, transform.position.y, transform.position.z);
	matrix = tmp*matrix;
}

void cg::GamePlay::MakeViewMatrix(Matrix4x4 &matrix)
{
	const Camera &camera = gs->camera;
	const Vector3 &camPos = camera.transform.position;
	const Vector3 &camRot = camera.transform.eulerRotation;

	Matrix4x4 tmp;
	Matrix4x4 root;
	root.SetIdentity();
	tmp.RotationZ(camRot.z);
	root = tmp*root;
	tmp.RotationY(camRot.y);
	root = tmp*root;
	tmp.RotationX(camRot.x);
	root = tmp*root;
	tmp.Transformation(camPos.x, camPos.y, camPos.z);
	root = tmp*root;
	Vector3 right = { root(0, 0), root(1, 0), root(2, 0) };
	Vector3 up = { root(0, 1), root(1, 1), root(2, 1) };
	Vector3 forward = { root(0, 2), root(1, 2), root(2, 2) };
	Vector3 pos = { root(0, 3), root(1, 3), root(2, 3) };

	matrix(0, 0) = right.x;
	matrix(0, 1) = right.y;
	matrix(0, 2) = right.z;
	matrix(0, 3) = -right*pos;

	matrix(1, 0) = up.x;
	matrix(1, 1) = up.y;
	matrix(1, 2) = up.z;
	matrix(1, 3) = -up*pos;

	matrix(2, 0) = forward.x;
	matrix(2, 1) = forward.y;
	matrix(2, 2) = forward.z;
	matrix(2, 3) = -forward*pos;

	matrix(3, 0) = 0;
	matrix(3, 1) = 0;
	matrix(3, 2) = 0;
	matrix(3, 3) = 1;
}

void cg::GamePlay::MakePerProjMatrix(Matrix4x4 &matrix)
{
	matrix.SetIdentity();
	const Camera &camera = gs->camera;
	matrix(0, 0) = 2 * camera.nearPlane / camera.width;
	matrix(1, 1) = 2 * camera.nearPlane / camera.height;
	matrix(2, 2) = camera.farPlane / (camera.farPlane - camera.nearPlane);
	matrix(2, 3) = camera.farPlane*camera.nearPlane / (camera.nearPlane - camera.farPlane);
	matrix(3, 2) = 1;
	matrix(3, 3) = 0;
}

void cg::GamePlay::MakeWindowMatrix(Matrix4x4 &matrix)
{
	matrix.SetIdentity();
	Matrix4x4 tmp;
	tmp.Scaling(canvas.width, canvas.height, 1);
	matrix = tmp*matrix;
	tmp.SetIdentity();
	tmp.Transformation(canvas.width / 2, -canvas.height / 2, 0);
	matrix = tmp*matrix;
	tmp.SetIdentity();
	tmp(1, 1) = -1;
	matrix = tmp*matrix;
}


bool cg::GamePlay::DrawColor(int n, COLORREF color)
{
	if (n < 0 || n >= canvas.Size())
		return false;
	colorCache[n] = color;
	return true;
}

bool cg::GamePlay::DrawColor(int x, int y, COLORREF color)
{

	return isLegalXY(x, y) && DrawColor(Index(x, y), color);
}

bool cg::GamePlay::DrawColor(const Vector2Int &v2, COLORREF color)
{
	return DrawColor(Index(v2), color);
}

void cg::GamePlay::FillTriangle(const VertexInt &a, const VertexInt &b, const VertexInt &c)
{
	using std::swap;
	unordered_map<int, vector<ACE>> edgeTable;
	int YMIN = a.y;
	int YMAX = a.y;

	const VertexInt *p[] = { &a, &b, &c };
	for (int i = 0; i < 3; ++i)
	{
		const VertexInt *pa = p[i];
		const VertexInt *pb = p[(i + 1) % 3];
		if (pa->y == pb->y)
			continue;
		if ((pa->y) >(pb->y))
		{
			swap(pa, pb);
		}
		YMIN = min(YMIN, pa->y);
		YMAX = max(YMAX, pb->y);
		float x = pa->x;
		float z = pa->z;
		ColorF color = pa->color;
		float dy = (pb->y - pa->y);
		float deltaX = float(pb->x - pa->x) / dy;
		float deltaZ = float(pb->z - pa->z) / dy;
		ColorF deltaColor = (pb->color - pa->color) / dy;
		int yMax = pb->y;
		edgeTable[pa->y].push_back({ x, z, color, deltaX, deltaZ, deltaColor, yMax });
	}

	vector<ACE> edge;
	for (int y = YMIN; y < YMAX; ++y)
	{
		if (edgeTable.find(y) != edgeTable.end())
		{
			edge.insert(edge.end(), edgeTable[y].begin(), edgeTable[y].end());
			sort(edge.begin(), edge.end());
		}

		if (!edge.empty())
		{
			int indexs[2] = { 0, 1 };
			VertexInt vert[2];
			if (edge.size() >= 3)
			{
				indexs[1] = 2;
			}
			for (int i = 0; i < 2; ++i)
			{
				int index = indexs[i];
				vert[i].x = int(edge[index].x + 0.5);
				vert[i].y = y;
				vert[i].z = edge[index].z;
				vert[i].color = edge[index].color;
			}
			HorizontalLine(vert[0], vert[1]);
		}
		for (auto it = edge.begin(); it != edge.end();)
		{
			if (it->yMax <= y)
			{
				it = edge.erase(it);
			}
			else
			{
				it->x += it->deltaX;
				it->z += it->deltaZ;
				it->color += it->deltaColor;
				++it;
			}
		}
	}
}

COLORREF & cg::GamePlay::ColorCache(int n)
{
	if (n < 0 || n >= canvas.Size())
		throw std::runtime_error("index is over");
	return colorCache[n];
}

COLORREF & cg::GamePlay::ColorCache(int x, int y)
{
	return ColorCache(Index(x, y));
}

COLORREF & cg::GamePlay::ColorCache(const Vector2Int &v2)
{
	return ColorCache(Index(v2));
}

float & cg::GamePlay::ZCache(int n)
{
	if (n < 0 || n >= canvas.Size())
		throw std::runtime_error("index is over");
	return zCache[n];
}

float & cg::GamePlay::ZCache(int x, int y)
{
	return ZCache(Index(x, y));
}

float & cg::GamePlay::ZCache(const Vector2Int &v2)
{
	return ZCache(Index(v2.x, v2.y));
}

bool cg::GamePlay::SetZIfLess(int n, float z)
{
	if (n < 0 || n >= canvas.Size())
		return false;
	if (z < zCache[n])
	{
		zCache[n] = z;
		return true;
	}
	return false;
}

bool cg::GamePlay::SetZIfLess(int x, int y, float z)
{
	if (!isLegal(x, y, z))
		return false;
	return SetZIfLess(Index(x, y), z);
}

bool cg::GamePlay::SetZIfLess(const Vector2Int &v2, float z)
{
	if (!isLegal(v2, z))
		return false;
	return SetZIfLess(Index(v2), z);
}

int cg::GamePlay::Index(int x, int y)
{
	return x + y * canvas.width;
}

int cg::GamePlay::Index(const Vector2Int &v2)
{
	return v2.x + v2.y * canvas.height;
}

void cg::GamePlay::Line(int x0, int y0, float z0, int x1, int y1, float z1, COLORREF color)
{
	using std::swap;
	if (y0 == y1)
	{
		if (x0 > x1)
		{
			swap(x0, x1);
			swap(z0, z1);
		}
		float d1 = x1 - x0;
		float dz = (z1 - z0) / d1;
		float z = z0;
		for (int x = x0; x <= x1; ++x)
		{
			if (SetZIfLess(Index(x, y0), z))
			{
				DrawColor(x, y0, color);
			}
			z += dz;
		}
		return;
	}

	if (x0 == x1)
	{
		if (y0 > y1)
		{
			swap(y0, y1);
			swap(z0, z1);
		}
		float d1 = y1 - y0;
		float dz = (z1 - z0) / d1;
		float z = z0;
		for (int y = y0; y <= y1; ++y)
		{
			if (SetZIfLess(Index(x0, y), z))
			{
				DrawColor(x0, y, color);
			}
			z += dz;
		}
		return;
	}
	if (x1 - x0 > 0 && y1 - y0 < 0) //位于第4象限
	{
		swap(x0, x1);
		swap(y0, y1);
		swap(z0, z1);
	}
	else if (x1 - x0 < 0 && y1 - y0 <= 0) //位于第3象限
	{
		swap(x0, x1);
		swap(y0, y1);
		swap(z0, z1);
	}
	int dx, dy;
	dx = x1 - x0;
	dy = y1 - y0;
	float k = float(dy) / dx;
	float g = float(dx) / dy;

	if (k >= 0 && k < 1) //斜率[0,1)
	{
		float d1 = x1 - x0;
		float dz = (z1 - z0) / d1;
		float z = z0;

		float _y = y0;
		for (int x = x0; x <= x1; ++x)
		{
			int y = int(_y + 0.5);
			if (SetZIfLess(Index(x, y), z))
			{
				DrawColor(x, y, color);
			}
			z += dz;
			_y += k;
		}
	}
	else if (k >= 1) //斜率[1,+00)
	{
		float d1 = y1 - y0;
		float dz = (z1 - z0) / d1;
		float z = z0;

		float _x = x0;
		for (int y = y0; y <= y1; ++y)
		{
			int x = int(_x + 0.5);
			if (SetZIfLess(Index(x, y), z))
			{
				DrawColor(x, y, color);
			}
			z += dz;
			_x += g;
		}
	}
	else if (k < -1) //斜率(-00,-1)
	{
		float d1 = y1 - y0;
		float dz = (z1 - z0) / d1;
		float z = z0;

		float _x = x0;
		for (int y = y0; y <= y1; ++y)
		{
			int x = int(_x + 0.5);
			if (SetZIfLess(Index(x, y), z))
			{
				DrawColor(x, y, color);
			}
			z += dz;
			_x += g;
		}
	}
	else if (k >= -1) //斜率[-1,0)
	{
		float d1 = x0 - x1;
		float dz = (z1 - z0) / d1;
		float z = z0;

		float _y = y0;
		for (int x = x0; x >= x1; --x)
		{
			int y = int(_y + 0.5);
			if (SetZIfLess(Index(x, y), z))
			{
				DrawColor(x, y, color);
			}
			z += dz;
			_y -= k;
		}
	}
}

void cg::GamePlay::Line(int x0, int y0, int x1, int y1, COLORREF color)
{
	using std::swap;
	if (y0 == y1)
	{
		if (x0 > x1)
			swap(x0, x1);
		for (int x = x0; x <= x1; ++x)
		{
			DrawColor(x, y0, color);
		}
		return;
	}

	if (x0 == x1)
	{
		if (y0 > y1)
			swap(y0, y1);
		for (int y = y0; y <= y1; ++y)
		{
			DrawColor(x0, y, color);
		}
		return;
	}
	if (x1 - x0 > 0 && y1 - y0 < 0) //位于第4象限
	{
		swap(x0, x1);
		swap(y0, y1);
	}
	else if (x1 - x0 < 0 && y1 - y0 <= 0) //位于第3象限
	{
		swap(x0, x1);
		swap(y0, y1);
	}
	int dx, dy;
	dx = x1 - x0;
	dy = y1 - y0;
	float k = float(dy) / dx;
	float _k = float(dx) / dy;

	if (k >= 0 && k < 1) //斜率[0,1)
	{
		float y = y0;
		for (int x = x0; x <= x1; ++x)
		{
			DrawColor(x, y, color);
			y += k;
		}
	}
	else if (k >= 1) //斜率[1,+00)
	{
		float x = x0;
		for (int y = y0; y <= y1; ++y)
		{
			DrawColor(x, y, color);
			x += _k;
		}
	}
	else if (k < -1) //斜率(-00,-1)
	{
		float x = x0;
		for (int y = y0; y <= y1; ++y)
		{
			DrawColor(x, y, color);
			x += _k;
		}
	}
	else if (k >= -1) //斜率[-1,0)
	{
		float y = y0;
		for (int x = x0; x >= x1; --x)
		{
			DrawColor(x, y, color);
			y -= k;
		}
	}
}

void cg::GamePlay::Line(const Vector2Int &a, const Vector2Int &b, COLORREF color)
{
	Line(a.x, a.y, b.x, b.y, color);
}

void cg::GamePlay::Line(const Vector3Int &a, const Vector3Int &b, COLORREF color)
{
	Line(a.x, a.y, a.z, b.x, b.y, b.z, color);
}

void cg::GamePlay::Line(int x0, int y0, int x1, int y1, COLORREF color0, COLORREF color1)
{
	using std::swap;
	ColorF c0(color0);
	ColorF c1(color1);
	if (y0 == y1)
	{
		if (x0 > x1)
		{
			swap(x0, x1);
			swap(c0, c1);
		}
		float d1 = x1 - x0;
		ColorF dc = (c1 - c0) / d1;
		ColorF c = c0;
		for (int x = x0; x <= x1; ++x)
		{
			DrawColor(x, y0, c.GetCOLORREF());
			c += dc;
		}
		return;
	}

	if (x0 == x1)
	{
		if (y0 > y1)
		{
			swap(y0, y1);
			swap(c0, c1);
		}
		float d1 = y1 - y0;
		ColorF dc = (c1 - c0) / d1;
		ColorF c = c0;
		for (int y = y0; y <= y1; ++y)
		{
			DrawColor(x0, y, c.GetCOLORREF());
			c += dc;
		}
		return;
	}
	if (x1 - x0 > 0 && y1 - y0 < 0) //位于第4象限
	{
		swap(x0, x1);
		swap(y0, y1);
		swap(c0, c1);
	}
	else if (x1 - x0 < 0 && y1 - y0 <= 0) //位于第3象限
	{
		swap(x0, x1);
		swap(y0, y1);
		swap(c0, c1);
	}
	int dx, dy;
	dx = x1 - x0;
	dy = y1 - y0;
	float k = float(dy) / dx;
	float g = float(dx) / dy;

	if (k >= 0 && k < 1) //斜率[0,1)
	{
		float d1 = x1 - x0;
		ColorF dc = (c1 - c0) / d1;
		ColorF c = c0;
		float _y = y0;
		for (int x = x0; x <= x1; ++x)
		{
			int y = int(_y + 0.5);
			DrawColor(x, y, c.GetCOLORREF());
			c += dc;
			_y += k;
		}
	}
	else if (k >= 1) //斜率[1,+00)
	{
		float d1 = y1 - y0;
		ColorF dc = (c1 - c0) / d1;
		ColorF c = c0;
		float _x = x0;
		for (int y = y0; y <= y1; ++y)
		{
			int x = int(_x + 0.5);
			DrawColor(x, y, c.GetCOLORREF());
			c += dc;
			_x += g;
		}
	}
	else if (k < -1) //斜率(-00,-1)
	{
		float d1 = y1 - y0;
		ColorF dc = (c1 - c0) / d1;
		ColorF c = c0;
		float _x = x0;
		for (int y = y0; y <= y1; ++y)
		{
			int x = int(_x + 0.5);
			DrawColor(x, y, c.GetCOLORREF());
			c += dc;
			_x += g;
		}
	}
	else if (k >= -1) //斜率[-1,0)
	{
		float d1 = x0 - x1;
		ColorF dc = (c1 - c0) / d1;
		ColorF c = c0;
		float _y = y0;
		for (int x = x0; x >= x1; --x)
		{
			int y = int(_y + 0.5);
			DrawColor(x, y, c.GetCOLORREF());
			c += dc;
			_y -= k;
		}
	}
}

void cg::GamePlay::Line(int x0, int y0, float z0, int x1, int y1, float z1, COLORREF color0, COLORREF color1)
{
	using std::swap;
	ColorF c0(color0);
	ColorF c1(color1);
	if (y0 == y1)
	{
		if (x0 > x1)
		{
			swap(x0, x1);
			swap(z0, z1);
			swap(c0, c1);
		}
		float d1 = x1 - x0;
		if (d1 == 0)
			return;
		float dz = (z1 - z0) / d1;
		ColorF dc = (c1 - c0) / d1;
		float z = z0;
		ColorF c = c0;
		for (int x = x0; x < x1; ++x)
		{
			if (SetZIfLess(x, y0, z))
			{
				DrawColor(x, y0, c.GetCOLORREF());
			}
			z += dz;
			c += dc;
		}
		return;
	}

	if (x0 == x1)
	{
		if (y0 > y1)
		{
			swap(y0, y1);
			swap(z0, z1);
			swap(c0, c1);
		}
		float d1 = y1 - y0;
		float dz = (z1 - z0) / d1;
		ColorF dc = (c1 - c0) / d1;
		float z = z0;
		ColorF c = c0;
		for (int y = y0; y <= y1; ++y)
		{
			if (SetZIfLess(x0, y, z))
			{
				DrawColor(x0, y, c.GetCOLORREF());
			}
			z += dz;
			c += dc;
		}
		return;
	}
	if (x1 - x0 > 0 && y1 - y0 < 0) //位于第4象限
	{
		swap(x0, x1);
		swap(y0, y1);
		swap(z0, z1);
		swap(c0, c1);
	}
	else if (x1 - x0 < 0 && y1 - y0 <= 0) //位于第3象限
	{
		swap(x0, x1);
		swap(y0, y1);
		swap(z0, z1);
		swap(c0, c1);
	}
	int dx, dy;
	dx = x1 - x0;
	dy = y1 - y0;
	float k = float(dy) / dx;
	float g = float(dx) / dy;

	if (k >= 0 && k < 1) //斜率[0,1)
	{
		float d1 = x1 - x0;
		float dz = (z1 - z0) / d1;
		ColorF dc = (c1 - c0) / d1;
		float z = z0;
		ColorF c = c0;
		float _y = y0;
		for (int x = x0; x <= x1; ++x)
		{
			int y = int(_y + 0.5);
			if (SetZIfLess(x, y, z))
			{
				DrawColor(x, y, c.GetCOLORREF());
			}
			z += dz;
			c += dc;
			_y += k;
		}
	}
	else if (k >= 1) //斜率[1,+00)
	{
		float d1 = y1 - y0;
		float dz = (z1 - z0) / d1;
		ColorF dc = (c1 - c0) / d1;
		float z = z0;
		ColorF c = c0;
		float _x = x0;
		for (int y = y0; y <= y1; ++y)
		{
			int x = int(_x + 0.5);
			if (SetZIfLess(x, y, z))
			{
				DrawColor(x, y, c.GetCOLORREF());
			}
			z += dz;
			c += dc;
			_x += g;
		}
	}
	else if (k < -1) //斜率(-00,-1)
	{
		float d1 = y1 - y0;
		float dz = (z1 - z0) / d1;
		ColorF dc = (c1 - c0) / d1;
		float z = z0;
		ColorF c = c0;
		float _x = x0;
		for (int y = y0; y <= y1; ++y)
		{
			int x = int(_x + 0.5);
			if (SetZIfLess(x, y, z))
			{
				DrawColor(x, y, c.GetCOLORREF());
			}
			z += dz;
			c += dc;
			_x += g;
		}
	}
	else if (k >= -1) //斜率[-1,0)
	{
		float d1 = x0 - x1;
		float dz = (z1 - z0) / d1;
		ColorF dc = (c1 - c0) / d1;
		float z = z0;
		ColorF c = c0;
		float _y = y0;
		for (int x = x0; x >= x1; --x)
		{
			int y = int(_y + 0.5);
			if (SetZIfLess(x, y, z))
			{
				DrawColor(x, y, c.GetCOLORREF());
			}
			z += dz;
			c += dc;
			_y -= k;
		}
	}
}

void cg::GamePlay::Line(const Vector3Int &a, const Vector3Int &b, COLORREF color0, COLORREF color1)
{
	Line(a.x, a.y, a.z, b.x, b.y, b.z, color0, color1);
}

void cg::GamePlay::Line(const Vector2Int &a, const Vector2Int &b, COLORREF color0, COLORREF color1)
{
	Line(a.x, a.y, b.x, b.y, color0, color1);
}

void cg::GamePlay::Line(const VertexInt &a, const VertexInt &b)
{
	Line(a.x, a.y, a.z, b.x, b.y, b.z, a.color.GetCOLORREF(), b.color.GetCOLORREF());
}

//void cg::GamePlay::TextureLine(int x0, int y0, float z0, int x1, int y1, float z1, COLORREF color0, COLORREF color1, const Matrix4x4 &viewMat, const Matrix4x4 &textureMat, const std::shared_ptr<Object> &pObject, const Vector2(&text)[3])
//{
//	using std::swap;
//	ColorF c0(color0);
//	ColorF c1(color1);
//	if (y0 == y1)
//	{
//		if (x0 > x1)
//		{
//			swap(x0, x1);
//			swap(z0, z1);
//			swap(c0, c1);
//		}
//		float d1 = x1 - x0;
//		float dz = (z1 - z0) / d1;
//		ColorF dc = (c1 - c0) / d1;
//		float z = z0;
//		ColorF c = c0;
//		Vector4 viewV4 = (viewMat*Vector4(x0, y0, z, 1));
//		Vector4 dView = (viewMat*Vector4(1, 0, dz, 0));
//		Vector4 abcd = (textureMat*viewV4);
//		Vector4 dabcd = (textureMat*dView);
//		for (int x = x0; x < x1; ++x)
//		{
//			if (SetZIfLess(x, y0, z))
//			{
//				//Vector3 abc = (textureMat*viewV4).GetVector3();
//				Vector3 abc = abcd.GetVector3();
//
//				//Vector4 viewV4 = (viewMat*Vector4(x, y0, z, 1));
//				//Vector3 abc = (textureMat*viewV4).GetVector3();
//
//				int width = pObject->pTexture->bmpWidth;
//				int height = pObject->pTexture->bmpHeight;
//				const PBYTE &pBits = pObject->pTexture->pBits;
//				//int s = abc.z * width;
//				//int t = abc.y * height;
//				int s = (abc.x*text[0].x + abc.y*text[1].x + abc.z*text[2].x)*width;
//				int t = (abc.x*text[0].y + abc.y*text[1].y + abc.z*text[2].y)*height;
//				s = (s% width + width) % width;
//				t = (t% height + height) % height;
//				int size = width*height;
//				int k = (s + t * height) * 3;
//				//if (index < 0 || index >= size)
//				//	continue;
//				COLORREF r = (COLORREF)(pBits[k + 2]) << 16;
//				COLORREF g = (COLORREF)(pBits[k + 1]) << 8;
//				COLORREF b = (COLORREF)(pBits[k + 0]) << 0;
//				COLORREF color = r | g | b;
//				ColorF cf(color);
//				Reflection ref;
//				ref.red = cf.red / 255;
//				ref.green = cf.green / 255;
//				ref.blue = cf.blue / 255;
//				ColorF _c = c*ref;
//				DrawColor(x, y0, _c);
//			}
//			z += dz;
//			c += dc;
//			viewV4 += dView;
//			abcd += dabcd;
//		}
//		return;
//	}
//
//	if (x0 == x1)
//	{
//		if (y0 > y1)
//		{
//			swap(y0, y1);
//			swap(z0, z1);
//			swap(c0, c1);
//		}
//		float d1 = y1 - y0;
//		float dz = (z1 - z0) / d1;
//		ColorF dc = (c1 - c0) / d1;
//		float z = z0;
//		ColorF c = c0;
//		for (int y = y0; y <= y1; ++y)
//		{
//			if (SetZIfLess(x0, y, z))
//			{
//				DrawColor(x0, y, c);
//			}
//			z += dz;
//			c += dc;
//		}
//		return;
//	}
//	if (x1 - x0 > 0 && y1 - y0 < 0) //位于第4象限
//	{
//		swap(x0, x1);
//		swap(y0, y1);
//		swap(z0, z1);
//		swap(c0, c1);
//	}
//	else if (x1 - x0 < 0 && y1 - y0 <= 0) //位于第3象限
//	{
//		swap(x0, x1);
//		swap(y0, y1);
//		swap(z0, z1);
//		swap(c0, c1);
//	}
//	int dx, dy;
//	dx = x1 - x0;
//	dy = y1 - y0;
//	float k = float(dy) / dx;
//	float g = float(dx) / dy;
//
//	if (k >= 0 && k < 1) //斜率[0,1)
//	{
//		float d1 = x1 - x0;
//		float dz = (z1 - z0) / d1;
//		ColorF dc = (c1 - c0) / d1;
//		float z = z0;
//		ColorF c = c0;
//		float _y = y0;
//		for (int x = x0; x <= x1; ++x)
//		{
//			int y = int(_y + 0.5);
//			if (SetZIfLess(x, y, z))
//			{
//				DrawColor(x, y, c);
//			}
//			z += dz;
//			c += dc;
//			_y += k;
//		}
//	}
//	else if (k >= 1) //斜率[1,+00)
//	{
//		float d1 = y1 - y0;
//		float dz = (z1 - z0) / d1;
//		ColorF dc = (c1 - c0) / d1;
//		float z = z0;
//		ColorF c = c0;
//		float _x = x0;
//		for (int y = y0; y <= y1; ++y)
//		{
//			int x = int(_x + 0.5);
//			if (SetZIfLess(x, y, z))
//			{
//				DrawColor(x, y, c);
//			}
//			z += dz;
//			c += dc;
//			_x += g;
//		}
//	}
//	else if (k < -1) //斜率(-00,-1)
//	{
//		float d1 = y1 - y0;
//		float dz = (z1 - z0) / d1;
//		ColorF dc = (c1 - c0) / d1;
//		float z = z0;
//		ColorF c = c0;
//		float _x = x0;
//		for (int y = y0; y <= y1; ++y)
//		{
//			int x = int(_x + 0.5);
//			if (SetZIfLess(x, y, z))
//			{
//				DrawColor(x, y, c);
//			}
//			z += dz;
//			c += dc;
//			_x += g;
//		}
//	}
//	else if (k >= -1) //斜率[-1,0)
//	{
//		float d1 = x0 - x1;
//		float dz = (z1 - z0) / d1;
//		ColorF dc = (c1 - c0) / d1;
//		float z = z0;
//		ColorF c = c0;
//		float _y = y0;
//		for (int x = x0; x >= x1; --x)
//		{
//			int y = int(_y + 0.5);
//			if (SetZIfLess(x, y, z))
//			{
//				DrawColor(x, y, c);
//			}
//			z += dz;
//			c += dc;
//			_y -= k;
//		}
//	}
//}
//
//void cg::GamePlay::TextureLine(const VertexInt &a, const VertexInt &b, const Matrix4x4 &viewMat, const Matrix4x4 &textureMat, const std::shared_ptr<Object> &pObject, const Vector2(&text)[3])
//{
//	TextureLine(a.x, a.y, a.z, b.x, b.y, b.z, a.color, b.color, viewMat, textureMat, pObject, text);
//}

void cg::GamePlay::AllocateCache()
{
	LONG sz = canvas.Size();
	colorCache = new COLORREF[sz];
	zCache = new float[sz];
}

void cg::GamePlay::ReleaseCache()
{
	delete[] colorCache;
	delete[] zCache;
	colorCache = nullptr;
	zCache = nullptr;
}

void cg::GamePlay::SetCanvas()
{
	RECT rc;
	GetClientRect(hWnd, &rc);
	canvas.x = rc.left;
	canvas.y = rc.top;
	canvas.width = rc.right - rc.left;
	canvas.height = rc.bottom - rc.top;
	canvas.aspect = float(canvas.width) / canvas.height;
}

void cg::GamePlay::InitCache()
{
	LONG sz = canvas.Size();
	memset(colorCache, 0, sizeof(COLORREF)* sz);
	for (int i = 0; i < sz; ++i)
		zCache[i] = 1;
}

void cg::GamePlay::SetBITMAPV4HEADER()
{
	memset(&bi, 0, sizeof bi);
	bi.bV4Size = sizeof bi;
	bi.bV4BitCount = 32;
	bi.bV4Planes = 1;
	bi.bV4Width = canvas.width;
	bi.bV4Height = -canvas.height;
	bi.bV4V4Compression = BI_BITFIELDS;
	bi.bV4AlphaMask = 0xFF000000;
	bi.bV4RedMask = 0x00FF0000;
	bi.bV4GreenMask = 0x0000FF00;
	bi.bV4BlueMask = 0x000000FF;
}

void cg::GamePlay::FillSolid()
{
	for (const shared_ptr<Object> &pObject : gs->objectList)
	{
		if (!pObject || !pObject->pMesh || !pObject->isActive)
			continue;
		Mesh &mesh = *(pObject->pMesh);

		/*坐标变换之WorldTransform And ViewTransform*/
		vector<Vector3> posList;
		vector<Mesh::Triangle> triangleList = mesh.triangleList;
		WorldAndViewTransform(posList, *pObject, triangleList);

		/*环境光照*/
		ColorF ambientLight = gs->pAmbientLight->color*pObject->pMaterial->ambient;
		if (pObject->pMaterial)
		{
			for (auto &vert : mesh.vertexList)
			{
				vert.color = ambientLight;
				/*vert.color = 0;*/
			}

			const auto &diff = pObject->pMaterial->diffuse;
			vector<vector<tuple<Vector3, float>>> nv(mesh.vertexList.size());
			/*为三角形的每个顶点计算法向量和面的权重*/
			for (Mesh::Triangle &triangle : mesh.triangleList)
			{
				Vector3 normal = triangle.Normal(posList).Normalized();
				for (int i = 0; i < 3; ++i)
				{
					const int index = triangle.indexs[i];
					int index1 = triangle.indexs[(i + 1) % 3];
					int index2 = triangle.indexs[(i + 2) % 3];
					Vector3 a = posList[index1] - posList[index];
					Vector3 b = posList[index2] - posList[index];
					float angle = Vector3::Angle(a, b);
					nv[index].emplace_back(normal, angle);
				}
			}
			for (int i = 0; i < mesh.vertexList.size(); ++i)
			{
				Vertex &vert = mesh.vertexList[i];
				float angle = 0;
				for (const tuple<Vector3, float> &tp : nv[i])
				{
					angle += get<1>(tp);
				}
				Vector3 normal(0, 0, 0);
				for (const tuple<Vector3, float> &tp : nv[i])
				{
					normal += get<0>(tp)*get<1>(tp) / angle;
				}
				vert.normal = normal;
			}
			for (int i = 0; i < mesh.vertexList.size(); ++i)
			{
				Vertex &vert = mesh.vertexList[i];
				Vector3 normal = vert.normal.Normalized();
				if (normalMode == NormalMode::Enable)
				{
					gs->lineList.push_back({ posList[i], posList[i] + normal });
				}
				for (const shared_ptr<Light> &pLight : gs->lightList)
				{
					if (pLight->isActive)
					{
						const Light &light = *pLight;
						Vector3 dist = (light.transform.position - posList[i]).Normalized();
						float cosAngle = dist*normal;
						float angle = Vector3::Angle(dist, normal);
						if (angle > 90)
							continue;
						ColorF color = light.color*cosAngle;
						if (!pObject->pTexture || !pObject->pTexture->isActive)
						{
							color *= diff;
						}
						vert.color += color;
						//vert.color = Clamp(vert.color, 0, 255);
					}
				}
			}


			vector<VertexInt> ivertList;
			Matrix4x4 tmp = ProAndWindowTransform(ivertList, posList);
			Matrix4x4 inver;
			bool isInver;
			/*纹理映射*/
			if (pObject->pTexture && pObject->pTexture->isActive)
			{
				isInver = tmp.Inverse(inver);
			}

			/*背面剔除*/
			for (Mesh::Triangle &triangle : mesh.triangleList)
			{
				BackFaceCulling(triangle, ivertList);
			}
			/*显示法线*/
			if (normalMode == NormalMode::Enable)
			{
				for (const Line3D &line : gs->lineList)
				{
					Vector3 delta = (line.to - line.from).Normalized() * normalShow.length;
					Vector3 to = line.from + delta;
					Line(line.from.x, line.from.y, line.from.z, to.x, to.y, to.z, normalShow.color);
				}
			}

			/*绘制物体的三角形面*/
			for (const Mesh::Triangle &triangle : mesh.triangleList)
			{
				if (triangle.isVisible)
				{
					int a = triangle.indexs[0];
					int b = triangle.indexs[1];
					int c = triangle.indexs[2];
					ivertList[a].color = mesh.vertexList[a].color;
					ivertList[b].color = mesh.vertexList[b].color;
					ivertList[c].color = mesh.vertexList[c].color;
					//ivertList[a].color = triangle.colors[0];
					//ivertList[b].color = triangle.colors[1];
					//ivertList[c].color = triangle.colors[2];
					const Vector2(&text)[3] = triangle.text;
					if (isLegal(ivertList[a]) || isLegal(ivertList[b]) || isLegal(ivertList[c]))
					{
						if (pObject->pTexture && pObject->pTexture->isActive)
						{
							TextureTriangle(ivertList[a], ivertList[b], ivertList[c], inver, pObject, text);
						}
						else
						{
							FillTriangle(ivertList[a], ivertList[b], ivertList[c]);
						}
					}
				}
			}
		}
	}
}



void cg::GamePlay::SetCamera(Camera &camera)
{
	//camera.width = canvas.width;
	//camera.height = canvas.height;
	//camera.angle = 60;
	//camera.nearPlane = camera.height / 2 / Tan(camera.angle / 2);
	//camera.farPlane = camera.nearPlane * 3;

	camera.angle = 120;
	camera.nearPlane = 100;
	camera.farPlane = 5000;
	camera.width = 2 * camera.nearPlane * Tan(camera.angle / 2);
	camera.height = camera.width / canvas.aspect;
}

bool cg::GamePlay::SetColorCache(int n, COLORREF color)
{
	if (n < 0 || n >= canvas.Size())
		return false;
	colorCache[n] = color;
	return true;
}

bool cg::GamePlay::SetColorCache(int x, int y, COLORREF color)
{
	return SetColorCache(Index(x, y), color);
}

bool cg::GamePlay::SetColorCache(const Vector2Int &v2, COLORREF color)
{
	return SetColorCache(Index(v2), color);
}

void cg::GamePlay::WorldAndViewTransform(std::vector<Vector3> &posList, const Object &object, std::vector<Mesh::Triangle> &triangleList)
{
	Matrix4x4 worldMat;
	MakeWorldMatrix(worldMat, object.transform);
	Matrix4x4 viewMat;
	MakeViewMatrix(viewMat);
	Matrix4x4 tmp = viewMat*worldMat;
	Mesh &mesh = *(object.pMesh);
	for (const Vertex &vert : mesh.vertexList)
	{
		Vector3 v = (tmp*(vert.GetVector4())).GetVector3();
		posList.push_back(v);
	}
	//if (!mesh.normalList.empty())
	//{
	//	Matrix4x4 normalMat;
	//	MakeNormalMatrix(normalMat, object.transform);
	//	for (int i = 0; i < mesh.triangleList.size(); ++i)
	//	{
	//		for (int j = 0; j < 3; ++j)
	//		{
	//			const Vector3 &normal = mesh.triangleList[i].normal[j];
	//			Vector3 n = (normalMat*(normal.GetVector4())).GetVector3();
	//			triangleList[i].normal[j] = n;
	//		}
	//	}
	//}
}

cg::Matrix4x4 cg::GamePlay::ProAndWindowTransform(std::vector<VertexInt> &ivertList, std::vector<Vector3> &posList)
{
	Matrix4x4 projMat;
	MakePerProjMatrix(projMat);
	Matrix4x4 winMat;
	MakeWindowMatrix(winMat);
	Matrix4x4 tmp = winMat*projMat;
	for (Vector3 &v : posList)
	{
		v = (tmp*v.GetVector4()).GetVector3();
		ivertList.push_back(VertexInt(int(0.5 + v.x), int(0.5 + v.y), v.z));
	}
	for (Line3D &line : gs->lineList)
	{
		line.from = (tmp*line.from.GetVector4()).GetVector3();
		line.to = (tmp*line.to.GetVector4()).GetVector3();
	}
	return tmp;
}

void cg::GamePlay::BackFaceCulling(Mesh::Triangle &triangle, const std::vector<VertexInt> &ivertList)
{
	if (cullingMode == CullingMode::Non)
	{
		triangle.isVisible = true;
		return;
	}
	const VertexInt &vert0 = ivertList[triangle.indexs[0]];
	const VertexInt &vert1 = ivertList[triangle.indexs[1]];
	const VertexInt &vert2 = ivertList[triangle.indexs[2]];
	float z = (vert1.x - vert0.x)*(vert2.y - vert1.y) - (vert2.x - vert1.x)*(vert1.y - vert0.y);
	bool back = z < 0;

	switch (cullingMode)
	{
	case cg::Front:
		triangle.isVisible = back;
		break;
	case cg::Back:
		triangle.isVisible = !back;
		break;
	default:
		break;
	}
}

bool cg::GamePlay::isLegal(int x, int y, float z) const
{
	return x >= 0 && x < canvas.width &&
		y >= 0 && y < canvas.height &&
		z >= 0 && z <= 1;
}

bool cg::GamePlay::isLegal(const Vector2Int &v2, float z) const
{
	return isLegal(v2.x, v2.y, z);
}

bool cg::GamePlay::isLegal(const Vector3Int &v3) const
{
	return isLegal(v3.x, v3.y, v3.z);
}

bool cg::GamePlay::isLegal(const VertexInt &vertex) const
{
	return isLegal(vertex.x, vertex.y, vertex.z);
}

void cg::GamePlay::DrawFPS()
{
	if (Time::deltaTime == 0)
		Time::deltaTime = 1;
	time_t t = CLOCKS_PER_SEC / Time::deltaTime;
	RECT rc;
	GetClientRect(hWnd, &rc);
	wchar_t p[10];
	swprintf_s(p, L"FPS: %I64d", t);
	DrawText(hdc, p, -1, &rc, DT_LEFT);
}

bool cg::GamePlay::isLegalXY(int x, int y) const
{
	return x >= 0 && x < canvas.width &&
		y >= 0 && y < canvas.height;
}

bool cg::GamePlay::isLegalXY(const Vector2Int &v2) const
{
	return isLegalXY(v2.x, v2.y);
}

bool cg::GamePlay::isLegalZ(float z) const
{
	return z >= 0.f && z <= 1.f;
}

void cg::GamePlay::ShowBitMap()
{
	PTSTR bmpFile = L".\\texture.bmp";
	PBITMAPFILEHEADER pBmpFileHeader;
	PBITMAPINFO pBmpInfo;
	PBYTE pBits = nullptr;
	LONG bmpWidth;
	LONG bmpHeight;
	DibTotalLoad(bmpFile, pBmpFileHeader, pBmpInfo, pBits, bmpWidth, bmpHeight);
	for (int i = 0; i < bmpWidth; ++i)
	for (int j = 0; j < bmpHeight; ++j)
	{
		if (pBmpInfo->bmiHeader.biBitCount == 24)
		{
			int k = (i + (540 - j) * 540) * 3;
			COLORREF r = (COLORREF)(pBits[k + 2]) << 16;
			COLORREF g = (COLORREF)(pBits[k + 1]) << 8;
			COLORREF b = (COLORREF)(pBits[k + 0]) << 0;
			COLORREF color = r | g | b;
			colorCache[Index(i, j)] = color;
		}
	}
	//for (int i = 150; i <= 300; ++i)
	//for (int j = 150; j <= 300; ++j)
	//{
	//	int index = Index(i, j);
	//	int k = i + (540-j) * 540;
	//	
	//	//COLORREF a = 0;
	//	//COLORREF r = (COLORREF)(pBits[k * 4 + 1]) << 16;
	//	//COLORREF g = (COLORREF)(pBits[k * 4 + 2]) << 8;
	//	//COLORREF b = (COLORREF)(pBits[k * 4 + 3]) << 0;
	//	color = pColor[k];
	//	colorCache[index] = color;
	//}

	//HDC mdc = CreateCompatibleDC(hdc);
	//HBITMAP bitMap = (HBITMAP)LoadImage
	//	(NULL,
	//	L"E:\\ComputerGraphics0810\\ComputerGraphics\\ComputerGraphics\\ComputerGraphics\\texture.bmp",
	//	IMAGE_BITMAP,
	//	canvas.width,
	//	canvas.height,
	//	LR_LOADFROMFILE);
	//SelectObject(mdc, bitMap);
	//BitBlt(hdc, 0, 0, canvas.width, canvas.height, mdc, 0, 0, SRCCOPY);
	//DeleteDC(mdc);

	//StretchDIBits(hdc,
	//	0, 0,
	//	canvas.width, canvas.height,
	//	0, 0,
	//	bmpWidth, bmpHeight,
	//	pBits, pBmpInfo,
	//	DIB_RGB_COLORS,
	//	SRCCOPY);
}

BOOL cg::GamePlay::DibTotalLoad(PTSTR bmpFIle, PBITMAPFILEHEADER &pBmpFileHeader, PBITMAPINFO &pBmpInfo, PBYTE &pBits, LONG &bmpWidth, LONG &bmpHeight)
{
	HANDLE hFile;
	hFile = CreateFile(bmpFIle,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_SEQUENTIAL_SCAN,
		NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return FALSE;
	DWORD fileSize;
	fileSize = GetFileSize(hFile, NULL);
	pBmpFileHeader = (PBITMAPFILEHEADER)malloc(fileSize);
	if (!pBmpFileHeader)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	DWORD bytesRead;
	BOOL isRead = ReadFile(hFile, pBmpFileHeader, fileSize, &bytesRead, NULL);
	CloseHandle(hFile);
	if (!isRead ||
		bytesRead != fileSize ||
		pBmpFileHeader->bfType != *(WORD *)"BM")
	{
		free(pBmpFileHeader);
		return FALSE;
	}

	pBmpInfo = (PBITMAPINFO)(pBmpFileHeader + 1);
	pBits = (PBYTE)(pBmpFileHeader)+pBmpFileHeader->bfOffBits;
	bmpWidth = pBmpInfo->bmiHeader.biWidth;
	bmpHeight = pBmpInfo->bmiHeader.biHeight;
	return TRUE;
}

void cg::GamePlay::TextureTriangle(const VertexInt &a, const VertexInt &b, const VertexInt &c, const Matrix4x4 &viewMat, const std::shared_ptr<Object> &pObject, const Vector2(&text)[3])
{
	Vector3 _pa = { (float)a.x, (float)a.y, (float)a.z };
	Vector3 _pb = { (float)b.x, (float)b.y, (float)b.z };
	Vector3 _pc = { (float)c.x, (float)c.y, (float)c.z };
	Vector3 pa = (viewMat*_pa.GetVector4()).GetVector3();
	Vector3 pb = (viewMat*_pb.GetVector4()).GetVector3();
	Vector3 pc = (viewMat*_pc.GetVector4()).GetVector3();
	Matrix4x4 _textMat =
	{ pa.x, pb.x, pc.x, 0,
	pa.y, pb.y, pc.y, 0,
	pa.z, pb.z, pc.z, 0,
	0, 0, 0, 1 };
	Matrix4x4 textureMat;
	_textMat.Inverse(textureMat);

	using std::swap;
	unordered_map<int, vector<ACE>> edgeTable;
	int YMIN = a.y;
	int YMAX = a.y;

	const VertexInt *p[] = { &a, &b, &c };
	for (int i = 0; i < 3; ++i)
	{
		const VertexInt *pa = p[i];
		const VertexInt *pb = p[(i + 1) % 3];
		if (pa->y == pb->y)
			continue;
		if ((pa->y) >(pb->y))
		{
			swap(pa, pb);
		}
		YMIN = min(YMIN, pa->y);
		YMAX = max(YMAX, pb->y);
		float x = pa->x;
		float z = pa->z;
		ColorF color = pa->color;
		float dy = (pb->y - pa->y);
		float deltaX = float(pb->x - pa->x) / dy;
		float deltaZ = float(pb->z - pa->z) / dy;
		ColorF deltaColor = (pb->color - pa->color) / dy;
		int yMax = pb->y;
		edgeTable[pa->y].push_back({ x, z, color, deltaX, deltaZ, deltaColor, yMax });
	}

	vector<ACE> edge;
	for (int y = YMIN; y < YMAX; ++y)
	{
		if (edgeTable.find(y) != edgeTable.end())
		{
			edge.insert(edge.end(), edgeTable[y].begin(), edgeTable[y].end());
			sort(edge.begin(), edge.end());
		}

		if (!edge.empty())
		{
			int indexs[2] = { 0, 1 };
			VertexInt vert[2];
			if (edge.size() >= 3)
			{
				indexs[1] = 2;
			}
			for (int i = 0; i < 2; ++i)
			{
				int index = indexs[i];
				vert[i].x = int(edge[index].x + 0.5);
				vert[i].y = y;
				vert[i].z = edge[index].z;
				vert[i].color = edge[index].color;
			}
			TextureHorizontalLine(vert[0], vert[1], viewMat, textureMat, pObject, text);
		}
		for (auto it = edge.begin(); it != edge.end();)
		{
			if (it->yMax <= y)
			{
				it = edge.erase(it);
			}
			else
			{
				it->x += it->deltaX;
				it->z += it->deltaZ;
				it->color += it->deltaColor;
				++it;
			}
		}
	}
}

void cg::GamePlay::DrawTriangle(const VertexInt &a, const VertexInt &b, const VertexInt &c)
{
	COLORREF color = ColorEnum::Red;
	if (isLegal(a) || isLegal(b) || isLegal(c))
	{
		Line(a.x, a.y, b.x, b.y, color);
		Line(b.x, b.y, c.x, c.y, color);
		Line(c.x, c.y, a.x, a.y, color);
	}
}

void cg::GamePlay::FillWireFrame()
{
	for (const shared_ptr<Object> &pObject : gs->objectList)
	{
		if (pObject == nullptr || pObject->pMesh == nullptr || !pObject->isActive)
			continue;
		Mesh &mesh = *(pObject->pMesh);

		/*从世界空间到窗口空间的变换*/
		vector<VertexInt> ivertList;
		WorldViewProWinTranform(ivertList, *pObject);

		/*背面剔除*/
		for (Mesh::Triangle &triangle : mesh.triangleList)
		{
			BackFaceCulling(triangle, ivertList);
		}

		COLORREF color = ColorEnum::Red;
		/*绘制物体的三角形面*/
		for (const Mesh::Triangle &triangle : mesh.triangleList)
		{
			if (triangle.isVisible)
			{
				int a = triangle.indexs[0];
				int b = triangle.indexs[1];
				int c = triangle.indexs[2];
				ivertList[a].color = color;
				ivertList[b].color = color;
				ivertList[c].color = color;
				DrawTriangle(ivertList[a], ivertList[b], ivertList[c]);
			}
		}
	}
}

void cg::GamePlay::WorldViewProWinTranform(std::vector<VertexInt> &ivertList, const Object &object)
{
	Matrix4x4 worldMat;
	MakeWorldMatrix(worldMat, object.transform);
	Matrix4x4 viewMat;
	MakeViewMatrix(viewMat);
	Matrix4x4 projMat;
	MakePerProjMatrix(projMat);
	Matrix4x4 winMat;
	MakeWindowMatrix(winMat);
	Matrix4x4 tmp = winMat * projMat * viewMat * worldMat;
	Mesh &mesh = *(object.pMesh);
	for (const Vertex &vert : mesh.vertexList)
	{
		Vector3 v = (tmp*(vert.GetVector4())).GetVector3();
		ivertList.push_back(VertexInt(int(0.5 + v.x), int(0.5 + v.y), v.z));
	}
}

void cg::GamePlay::Refresh()
{
	SetCanvas();
	SetBITMAPV4HEADER();
	ReleaseCache();
	AllocateCache();
	SetCamera(gs->camera);
}

void cg::GamePlay::MakeNormalMatrix(Matrix4x4 &matrix, const Transform &transform)
{
	matrix.SetIdentity();
	Matrix4x4 tmp;
	tmp.RotationZ(transform.eulerRotation.z);
	matrix = tmp*matrix;
	tmp.RotationY(transform.eulerRotation.y);
	matrix = tmp*matrix;
	tmp.RotationX(transform.eulerRotation.x);
	matrix = tmp*matrix;
	//const Camera &camera = gs->camera;
	//const Vector3 &camRot = camera.transform.eulerRotation;

	//Matrix4x4 root;
	//root.SetIdentity();
	//tmp.RotationZ(camRot.z);
	//root = tmp*root;
	//tmp.RotationY(camRot.y);
	//root = tmp*root;
	//tmp.RotationX(camRot.x);
	//root = tmp*root;
	//Vector3 right = { root(0, 0), root(1, 0), root(2, 0) };
	//Vector3 up = { root(0, 1), root(1, 1), root(2, 1) };
	//Vector3 forward = { root(0, 2), root(1, 2), root(2, 2) };

	//root(0, 0) = right.x;
	//root(0, 1) = right.y;
	//root(0, 2) = right.z;
	//root(0, 3) = 0;

	//root(1, 0) = up.x;
	//root(1, 1) = up.y;
	//root(1, 2) = up.z;
	//root(1, 3) = 0;

	//root(2, 0) = forward.x;
	//root(2, 1) = forward.y;
	//root(2, 2) = forward.z;
	//root(2, 3) = 0;

	//root(3, 0) = 0;
	//root(3, 1) = 0;
	//root(3, 2) = 0;
	//root(3, 3) = 1;

	//matrix = root*matrix;
}

void cg::GamePlay::HorizontalLine(int y, int x0, int x1, float z0, float z1, ColorF c0, ColorF c1)
{
	//#define __TEST__
#ifdef __TEST__
	string s;
	stringstream ss;
#endif // __TEST__
	using std::swap;
	if (x0 > x1)
	{
		swap(x0, x1);
		swap(z0, z1);
		swap(c0, c1);
	}
	float d1 = x1 - x0;
	if (d1 == 0)
		return;
	float dz = (z1 - z0) / d1;
	ColorF dc = (c1 - c0) / d1;
	float z = z0;
	ColorF c = c0;
	for (int x = x0; x < x1; ++x)
	{
		if (x == x0)
		{
			if (SetZIfLess(x, y, z))
			{
				//ColorF _c;
				//_c = c + dc * 2;
				DrawColor(x, y, c);
			}
			z += dz;
			c += dc;
			continue;
		}

		if (SetZIfLess(x, y, z))
		{
			DrawColor(x, y, c);
		}
		z += dz;
		c += dc;
	}
}

void cg::GamePlay::HorizontalLine(const VertexInt &a, const VertexInt &b)
{
	if (a.y != b.y)
		throw runtime_error("");
	HorizontalLine(a.y, a.x, b.x, a.z, b.z, a.color, b.color);
}

void cg::GamePlay::TextureHorizontalLine(int y, int x0, float z0, ColorF c0, int x1, float z1, ColorF c1, const Matrix4x4 &viewMat, const Matrix4x4 &textureMat, const std::shared_ptr<Object> &pObject, const Vector2(&text)[3])
{
	using std::swap;
	if (x0 > x1)
	{
		swap(x0, x1);
		swap(z0, z1);
		swap(c0, c1);
	}
	float d1 = x1 - x0;
	float dz = (z1 - z0) / d1;
	ColorF dc = (c1 - c0) / d1;
	float z = z0;
	ColorF c = c0;
	Vector4 viewV4 = (viewMat*Vector4(x0, y, z, 1));
	Vector4 dView = (viewMat*Vector4(1, 0, dz, 0));
	Vector4 abcd = (textureMat*viewV4);
	Vector4 dabcd = (textureMat*dView);
	for (int x = x0; x < x1; ++x)
	{
		if (SetZIfLess(x, y, z))
		{
			//Vector3 abc = (textureMat*viewV4).GetVector3();
			Vector3 abc = abcd.GetVector3();

			//Vector4 viewV4 = (viewMat*Vector4(x, y0, z, 1));
			//Vector3 abc = (textureMat*viewV4).GetVector3();

			int width = pObject->pTexture->bmpWidth;
			int height = pObject->pTexture->bmpHeight;
			const PBYTE &pBits = pObject->pTexture->pBits;
			//int s = abc.z * width;
			//int t = abc.y * height;
			int s = (abc.x*text[0].x + abc.y*text[1].x + abc.z*text[2].x)*width;
			int t = (abc.x*text[0].y + abc.y*text[1].y + abc.z*text[2].y)*height;
			s = (s% width + width) % width;
			t = (t% height + height) % height;
			int size = width*height;
			int k = (s + t * height) * 3;
			//if (index < 0 || index >= size)
			//	continue;
			COLORREF r = (COLORREF)(pBits[k + 2]) << 16;
			COLORREF g = (COLORREF)(pBits[k + 1]) << 8;
			COLORREF b = (COLORREF)(pBits[k + 0]) << 0;
			COLORREF color = r | g | b;
			ColorF cf(color);
			Reflection ref;
			ref.red = cf.red / 255;
			ref.green = cf.green / 255;
			ref.blue = cf.blue / 255;
			ColorF _c = c*ref;
			DrawColor(x, y, _c.GetCOLORREF());
		}
		z += dz;
		c += dc;
		viewV4 += dView;
		abcd += dabcd;
	}
}

void cg::GamePlay::TextureHorizontalLine(const VertexInt &a, const VertexInt &b, const Matrix4x4 &viewMat, const Matrix4x4 &textureMat, const std::shared_ptr<Object> &pObject, const Vector2(&text)[3])
{
	if (a.y != b.y)
		throw runtime_error("");
	TextureHorizontalLine(a.y, a.x, a.z, a.color, b.x, b.z, b.color, viewMat, textureMat, pObject, text);
}

bool cg::GamePlay::DrawColor(int n, const ColorF &color)
{
	return DrawColor(n, color.GetCOLORREF());
}

bool cg::GamePlay::DrawColor(int x, int y, const ColorF &color)
{
	return DrawColor(Index(x, y), color.GetCOLORREF());
}

bool cg::GamePlay::DrawColor(const Vector2Int &v2, const ColorF &color)
{
	return DrawColor(Index(v2), color.GetCOLORREF());
}
