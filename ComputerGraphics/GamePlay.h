#ifndef CG_GAMEPLAY_H
#define CG_GAMEPLAY_H
#include "stdafx.h"
#include "Canvas.h"
#include "GameSpace.h"
#include "Matrix4x4.h"
#include <functional>
#include <map>
CG_BEGIN
struct Vector2Int;
struct Vector3Int;
class GamePlay
{
public:
	GamePlay(HWND hWnd);
	~GamePlay();
	bool isActive = true;
	void Render();
	void Tick();
	void Refresh();
	void DoFrame();
	void InitCanvas();
	void InitGame();
private:
	/*����Ⱦ*/
	void FillSolid();
	/*�߿���Ⱦ*/
	void FillWireFrame();
	void SetCamera(Camera &camera);
	void SetBITMAPV4HEADER();
	void SetCanvas();
	void DrawFPS();
	void ShowBitMap();
	BOOL DibTotalLoad(PTSTR bmpFile,
		PBITMAPFILEHEADER &pBmpFileHeader,
		PBITMAPINFO &pBmpInfo,
		PBYTE &pBits,
		LONG &bmpWidth,
		LONG &bmpHeight
		);

	void AllocateCache();
	void ReleaseCache();
	void InitCache();

	/*����任*/
	void WorldAndViewTransform(std::vector<Vector3> &posList, const Object &object, std::vector<Mesh::Triangle> &triangleList);
	Matrix4x4 ProAndWindowTransform(std::vector<VertexInt> &ivertList, std::vector<Vector3> &posList);
	void WorldViewProWinTranform(std::vector<VertexInt> &ivertList, const Object &object);


	/*������*/
	//void DiffuseReflection()

	/*�����޳�*/
	void BackFaceCulling(Mesh::Triangle &triangle, const std::vector<VertexInt> &ivertList);


	/*���ɱ任����*/
	void MakeWorldMatrix(Matrix4x4 &matrix, const Transform &transform);
	void MakeViewMatrix(Matrix4x4 &matrix);
	void MakePerProjMatrix(Matrix4x4 &matrix);
	void MakeWindowMatrix(Matrix4x4 &matrix);
	void MakeNormalMatrix(Matrix4x4 &matrix, const Transform &transform);

	//void FillTriangle(const Vector3Int &a, const Vector3Int &b, const Vector3Int &c, COLORREF aColor, COLORREF bColor, COLORREF cColor);

	/*���������*/
	void FillTriangle(const VertexInt &a, const VertexInt &b, const VertexInt &c);
	/*��������*/
	void DrawTriangle(const VertexInt &a, const VertexInt &b, const VertexInt &c);
	/*����������*/
	void TextureTriangle(const VertexInt &a, const VertexInt &b, const VertexInt &c, const Matrix4x4 &viewMat, const std::shared_ptr<Object> &pObject, const Vector2(&text)[3]);

	/*��ɫ����*/
	void Line(int x0, int y0, int x1, int y1, COLORREF color);
	void Line(const Vector2Int &a, const Vector2Int &b, COLORREF color);

	void Line(int x0, int y0, float z0, int x1, int y1, float z1, COLORREF color);
	void Line(const Vector3Int &a, const Vector3Int &b, COLORREF color);

	/*��ֵ����*/
	void Line(int x0, int y0, int x1, int y1, COLORREF color0, COLORREF color1);
	void Line(const Vector2Int &a, const Vector2Int &b, COLORREF color0, COLORREF color1);

	void Line(int x0, int y0, float z0, int x1, int y1, float z1, COLORREF color0, COLORREF color1);
	void Line(const Vector3Int &a, const Vector3Int &b, COLORREF color0, COLORREF color1);
	void Line(const VertexInt &a, const VertexInt &b);

	void HorizontalLine(int y, int x0, int x1, float z0, float z1, ColorF c0, ColorF c1);
	void HorizontalLine(const VertexInt &a, const VertexInt &b);

	/*������*/
	void TextureHorizontalLine(int y, int x0, float z0, ColorF c0, int x1, float z1, ColorF c1, const Matrix4x4 &viewMat, const Matrix4x4 &textureMat, const std::shared_ptr<Object> &pObject, const Vector2(&text)[3]);
	void TextureHorizontalLine(const VertexInt &a, const VertexInt &b, const Matrix4x4 &viewMat, const Matrix4x4 &textureMat, const std::shared_ptr<Object> &pObject, const Vector2(&text)[3]);
	/*void TextureLine(int x0, int y0, float z0, int x1, int y1, float z1, COLORREF color0, COLORREF color1, const Matrix4x4 &viewMat, const Matrix4x4 &textureMat, const std::shared_ptr<Object> &pObject, const Vector2(&text)[3]);
	void TextureLine(const VertexInt &a, const VertexInt &b, const Matrix4x4 &viewMat, const Matrix4x4 &textureMat, const std::shared_ptr<Object> &pObject, const Vector2(&text)[3]);*/

	bool DrawColor(int n, COLORREF color);
	bool DrawColor(int x, int y, COLORREF color);
	bool DrawColor(const Vector2Int &v2, COLORREF color);
	bool DrawColor(int n, const ColorF &color);
	bool DrawColor(int x, int y, const ColorF &color);
	bool DrawColor(const Vector2Int &v2, const ColorF &color);

	COLORREF &ColorCache(int n);
	COLORREF &ColorCache(int x, int y);
	COLORREF &ColorCache(const Vector2Int &v2);

	bool SetColorCache(int n, COLORREF color);
	bool SetColorCache(int x, int y, COLORREF color);
	bool SetColorCache(const Vector2Int &v2, COLORREF color);

	float &ZCache(int n);
	float &ZCache(int x, int y);
	float &ZCache(const Vector2Int &v2);

	bool SetZIfLess(int n, float z);
	bool SetZIfLess(int x, int y, float z);
	bool SetZIfLess(const Vector2Int &v2, float z);



	/*������������*/
	int Index(int x, int y);
	int Index(const Vector2Int &v2);

	bool isLegalXY(int x, int y) const;
	bool isLegalXY(const Vector2Int &v2) const;

	bool isLegalZ(float z) const;

	bool isLegal(int x, int y, float z) const;
	bool isLegal(const Vector2Int &v2, float z) const;
	bool isLegal(const Vector3Int &v3) const;
	bool isLegal(const VertexInt &vertex) const;

	/*ɨ��������㷨��Ҫ�õ��Ľṹ*/
	struct ACE
	{
		float x;
		float z;
		ColorF color;
		float deltaX;
		float deltaZ;
		ColorF deltaColor;
		int yMax;
		//int index;
		friend bool operator <(const ACE &left, const ACE &right)
		{
			return left.x < right.x;
		}
	};

	/*��Ϸ�ռ�ָ��*/
	GameSpace *gs;

	/*��ɫ����*/
	COLORREF *colorCache;

	/*Z����*/
	float *zCache;

	/*���ھ��*/
	HWND hWnd;
	HDC hdc;

	BITMAPV4HEADER bi;

	/*�����޳�ģʽ*/
	CullingMode cullingMode = CullingMode::Back;
	/*��Ⱦģʽ*/
	FillMode fillMode = FillMode::Solid;
	/*������ʾģʽ*/
	NormalMode normalMode = NormalMode::Disable;
	NormalShow normalShow ={ ColorEnum::Red, 25 };

};
CG_END
#endif // CG_GAMEPLAY_H