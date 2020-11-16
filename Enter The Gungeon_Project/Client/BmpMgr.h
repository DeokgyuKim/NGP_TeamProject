#pragma once
class CBmp;
class CBmpMgr
{
private:
	static CBmpMgr*	m_pInstance;
	map<const TCHAR*, CBmp*> m_mapBmp;
public:
	HDC		Get_MemDC(const TCHAR* pKey);
	HBITMAP	Get_Bmp(const TCHAR* pKey);
	void	Insert_Bmp(const TCHAR* pPath, const TCHAR* pKey);
	void	Release();
public:
	static CBmpMgr* Get_Instance() {
		if (m_pInstance == nullptr)
			m_pInstance = new CBmpMgr;
		return m_pInstance;
	}
	static void		Destroy_Instance() {
		if (m_pInstance)
			delete m_pInstance;
		m_pInstance = nullptr;
	}
private:
	CBmpMgr();
	CBmpMgr(CBmpMgr& _rVal) {}
	void operator=(CBmpMgr& _rVal) {}
	~CBmpMgr();
};

