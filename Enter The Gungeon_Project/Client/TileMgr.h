#pragma once
class CObj;
class CTileMgr
{
private:
	vector<CObj*> m_vecTile;
	int		m_iX;
	int		m_iY;
public:
	void	Set_TILEXY(int iX, int iY) { m_iX = iX; m_iY = iY; }
	vector<CObj*>* Get_Tile() { return &m_vecTile; }
	int*	Get_CullSize();
	int*	Get_CullSize(INFO* pInfo, int iDist);
	void	Set_TileOption(int x, int y, int option);
	void	Initialize();
	void	Render(HDC hDC, bool bGuideLine);
	void	Render(HDC hDC, int iC);
	void	RenderAll(HDC hDC, int iC);
	void	Release();
	void	PickingTile(POINT& rPt, bool bPlus);
	void	PickingTile(POINT& rPt, int DrawID);
	void	SaveData();
	void	LoadData();
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

