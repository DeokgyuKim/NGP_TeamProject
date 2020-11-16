#pragma once
class CObj; 
class CMainGame
{
public:
	CMainGame();
	~CMainGame();
public:
	void Initialize(); 
	void Update(); 
	void LateUpdate(); 
	void Render(); 
	void Release(); 

private:
	HDC m_hDC;
	int m_iFPS; 
	TCHAR m_szFPS[32];
	DWORD m_dwOldTime; 
};

