#pragma once
class CBmp
{
public:
	CBmp();
	~CBmp();
public:
	HDC		Get_MemDC() { return m_hMemDC; }
public:
	void	Insert_Bmp(const TCHAR* pFilePath);
	HBITMAP	Get_Bmp() { return m_hBmp; }
	void	Release();
private:
	HDC		m_hMemDC;
	HBITMAP m_hBmp;
	HBITMAP m_hOldBmp;
};

