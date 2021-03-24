#ifndef CG_TEXTURE_H
#define CG_TEXTURE_H
#include "stdafx.h"
#include "Component.h"
#include "Reflection.h"
CG_BEGIN
class Texture :public Component
{
public:
	PTSTR bmpFile = L".\\texture.bmp";
	PBITMAPFILEHEADER pBmpFileHeader;
	PBITMAPINFO pBmpInfo;
	PBYTE pBits;
	LONG bmpWidth;
	LONG bmpHeight;
	bool LoadMap();
};
CG_END
#endif // !CG_TEXTURE_H

