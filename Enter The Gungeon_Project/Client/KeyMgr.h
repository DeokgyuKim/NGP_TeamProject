#pragma once
#define VK_MAX		0xff
class CKeyMgr
{
private:
	bool	m_bKeyState[VK_MAX];
public:
	bool	KeyPressing(int iKey);
	bool	KeyDown(int iKey);
	bool	KeyUp(int iKey);
	void	UpdateState();

public:
	static CKeyMgr*		Get_Instance() {
		if (nullptr == m_pInstance)
			m_pInstance = new CKeyMgr;
		return m_pInstance;
	}
	static void			Destroy_Instance() {
		if (m_pInstance)
			delete m_pInstance;
		m_pInstance = nullptr;
	}
private:
	static CKeyMgr*		m_pInstance;
private:
	CKeyMgr() { ZeroMemory(m_bKeyState, sizeof(m_bKeyState)); }
	CKeyMgr(CKeyMgr& _rVal) {}
	void operator=(CKeyMgr& _rVal) {}
	~CKeyMgr() {}
};

