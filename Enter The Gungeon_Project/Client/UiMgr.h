#pragma once
class CObj;
class CUiMgr
{
private:
	CObj*	m_pPlayer;
	CObj*	m_pBoss;
	bool	m_bMapOn;
public:
	void	Render(HDC hDC);
	void	Set_MapOn(bool bMapOn) { m_bMapOn = bMapOn; }
public:
	static CUiMgr*		Get_Instance() {
		if (nullptr == m_pInstance)
			m_pInstance = new CUiMgr;
		return m_pInstance;
	}
	static void			Destroy_Instance() {
		if (m_pInstance)
			delete m_pInstance;
		m_pInstance = nullptr;
	}
private:
	static CUiMgr*		m_pInstance;
private:
	CUiMgr();
	CUiMgr(CUiMgr& _rVal) {}
	void operator=(CUiMgr& _rVal) {}
	~CUiMgr() {}
};

