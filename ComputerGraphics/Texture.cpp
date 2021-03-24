#include "stdafx.h"
#include "Texture.h"

bool cg::Texture::LoadMap()
{
	HANDLE hFile;
	hFile = CreateFile(bmpFile,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_SEQUENTIAL_SCAN,
		NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return false;
	DWORD fileSize;
	fileSize = GetFileSize(hFile, NULL);
	pBmpFileHeader = (PBITMAPFILEHEADER)malloc(fileSize);
	if (!pBmpFileHeader)
	{
		CloseHandle(hFile);
		return false;
	}
	DWORD bytesRead;
	BOOL isRead = ReadFile(hFile, pBmpFileHeader, fileSize, &bytesRead, NULL);
	CloseHandle(hFile);
	if (!isRead ||
		bytesRead != fileSize ||
		pBmpFileHeader->bfType != *(WORD *)"BM")
	{
		free(pBmpFileHeader);
		return false;
	}

	pBmpInfo = (PBITMAPINFO)(pBmpFileHeader + 1);
	pBits = (PBYTE)(pBmpFileHeader)+pBmpFileHeader->bfOffBits;
	bmpWidth = pBmpInfo->bmiHeader.biWidth;
	bmpHeight = pBmpInfo->bmiHeader.biHeight;
	return true;
}
