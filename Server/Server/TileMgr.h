#pragma once
#include <Windows.h>
#include <vector>

using namespace std;

class CObj;
class CTileMgr
{
private:
	vector<CObj*> m_vecTile;
	int		m_iX;
	int		m_iY;
public:
	int*	Get_CullSize(float fX, float fY, int iDist);
	void	Set_TILEXY(int iX, int iY) { m_iX = iX; m_iY = iY; }
	vector<CObj*>* Get_Tile() { return &m_vecTile; }
	void	Set_TileOption(int x, int y, int option);
	void	Initialize();
	void	Release();
	void	LoadData(TCHAR* pChar);
	void	Clear();
private:
	static	CTileMgr*	m_pInstance;
public:
	static	CTileMgr*	Get_Instance() {
		if (m_pInstance == nullptr)
			m_pInstance = new CTileMgr;
		return m_pInstance;
	}
	static	void		Destroy_Instance() {
		if (m_pInstance)
			delete m_pInstance;
		m_pInstance = nullptr;
	}
private:
	CTileMgr() {}
	CTileMgr(const CTileMgr& _rVal) {}
	void operator=(const CTileMgr& _rVal) {}
	~CTileMgr() {}
};

