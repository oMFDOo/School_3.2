#include <stdio.h>
#include "dib.h"

MyDib::MyDib()
{
	m_hFile = NULL;
	m_hBitmap = NULL;
	m_lpBmih = NULL;
	m_dwSizeImage = 0;
	m_lpImage = NULL;
	m_bCompressed = FALSE;
	Empty();
}

MyDib::~MyDib()
{
	Empty();
}

int MyDib::GetHeight()
{
	if (m_lpBmih == NULL) return 0;
	return m_lpBmih->biHeight;
}
int MyDib::GetWidth()
{
	if (m_lpBmih == NULL) return 0;
	return m_lpBmih->biWidth;
}

BOOL MyDib::ReadBMP(char* strFilename)
{
	Empty();
	int iCount, iSize;
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	LPBYTE pbyBuffer;

	FILE* fp = NULL;
	fopen_s(&fp, strFilename, "rb");
	if (fp == NULL) {
		printf("file open error\n");
		return FALSE;
	}

	iCount = fread((LPVOID)&bmfh, sizeof(BITMAPFILEHEADER), 1, fp);
	if (iCount != 1) {
		printf("file read error\n");
		return FALSE;
	}
	if (bmfh.bfType != 0x4d42) {
		printf("invalid file\n");
		return FALSE;
	}
	iSize = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);
	pbyBuffer = new BYTE[iSize];
	iCount = fread(pbyBuffer, iSize, 1, fp); // info hdr & color table
	bmih = *(BITMAPINFOHEADER*)pbyBuffer;

	m_dwSizeImage = bmih.biSizeImage;

	if (m_dwSizeImage == 0)
		m_dwSizeImage = ComputeMetrics(CSize(bmih.biWidth, bmih.biHeight), bmih.biBitCount);
	ComputePaletteSize(bmih.biBitCount);

	m_lpBmih = (LPBITMAPINFOHEADER)new unsigned char[sizeof(BITMAPINFOHEADER) + m_iColorTableEntries * sizeof(RGBQUAD)];
	memcpy(m_lpBmih, pbyBuffer, iSize);
	delete[] pbyBuffer;
	m_lpvColorTable = (LPBYTE)m_lpBmih + sizeof(BITMAPINFOHEADER);
	m_lpImage = new BYTE[m_dwSizeImage];

	iCount = fread(m_lpImage, m_dwSizeImage, 1, fp);
	fclose(fp);
	return TRUE;
}


// helper functions
void MyDib::ComputePaletteSize(int iBitCount)
{
	if (m_lpBmih == NULL || m_lpBmih->biClrUsed == 0 || iBitCount > 8) {
		switch (iBitCount) {
		case 1:
			m_iColorTableEntries = 2;
			break;
		case 4:
			m_iColorTableEntries = 16;
			break;
		case 8:
			m_iColorTableEntries = 256;
			break;
		case 16:
		case 24:
		case 32:
			m_iColorTableEntries = 0;
			break;
		default:
			;
		}
	}
	else {
		m_iColorTableEntries = m_lpBmih->biClrUsed;
	}
}

int MyDib::ComputeMetrics(const CSize& szImage, int iBitCount)
{
	int iBytes = (szImage.cx * iBitCount) / 32;
	if ((szImage.cx * iBitCount) % 32) {
		iBytes++;
	}
	iBytes *= (4 * szImage.cy);

	return iBytes;
}

void MyDib::Empty()
{
	if (m_lpBmih) {
		delete[] m_lpBmih;
		m_lpBmih = NULL;
	}

	if (m_hBitmap != NULL) {
		::DeleteObject(m_hBitmap);
		m_hBitmap = NULL;
	}

	if (m_lpImage) {
		delete[] m_lpImage;
		m_lpImage = NULL;
	}


	m_lpvColorTable = NULL;
	m_iColorTableEntries = 0;
	m_dwSizeImage = 0;
	m_lpvFile = NULL;
	m_hMap = NULL;
	m_hFile = NULL;
	m_bCompressed = FALSE;
}

DWORD MyDib::Bpl()
{
	DWORD dwBytes = ((DWORD)m_lpBmih->biWidth * m_lpBmih->biBitCount) / 32;
	if (((DWORD)m_lpBmih->biWidth * m_lpBmih->biBitCount) % 32)
		dwBytes++;
	dwBytes *= 4;

	return dwBytes;
}
