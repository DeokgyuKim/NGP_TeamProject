#include "stdafx.h"
#include "Bmp.h"


CBmp::CBmp()
{
}


CBmp::~CBmp()
{
}

void CBmp::Insert_Bmp(const TCHAR * pFilePath)
{
	HDC hDC = GetDC(g_hWND);
	m_hMemDC = CreateCompatibleDC(hDC);
	ReleaseDC(g_hWND, hDC);
	m_hBmp = (HBITMAP)LoadImage(nullptr, pFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBmp);
}

void CBmp::Release()
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteObject(m_hBmp);
	DeleteDC(m_hMemDC);
}
