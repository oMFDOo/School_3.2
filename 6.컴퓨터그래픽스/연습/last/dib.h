#pragma once
#pragma once
#include "Windows.h"
class CSize
{
public:
	int cx, cy;
public:
	CSize(int x, int y) { cx = x; cy = y; };

};
class MyDib
{
public:
	LPVOID m_lpvColorTable;
	HBITMAP m_hBitmap;				// DIB object
	LPBYTE m_lpImage;				// starting address of DIB bits
	LPBITMAPINFOHEADER m_lpBmih;	// buffer containing the BITMAPINFOHEADER
private:
	DWORD m_dwSizeImage; // of bits -- not BITMAPINFOHEADER
						 //  or BITMAPFILEHEADER
	HANDLE m_hFile;
	HANDLE m_hMap;
	LPVOID m_lpvFile;
	int m_iColorTableEntries;
	BOOL m_bCompressed;
private:
	void ComputePaletteSize(int iBitCount);
	int ComputeMetrics(const CSize& szImage, int iBitCount);
public:
	MyDib();
	~MyDib();
	BOOL ReadBMP(char* strFilename);

	int GetSizeImage() { return m_dwSizeImage; }
	int GetSizeHeader() { return sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_iColorTableEntries; }
	int GetWidth();
	int GetHeight();

	void Empty();
	DWORD Bpl();
};
