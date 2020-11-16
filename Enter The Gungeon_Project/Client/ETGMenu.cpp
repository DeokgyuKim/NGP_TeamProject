#include "stdafx.h"
#include "ETGMenu.h"

#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

void CETGMenu::FrameMove()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		m_tFrame.iFrameStart += m_tFrame.iPlus;
		m_tFrame.dwFrameTime = GetTickCount();
	}
	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		m_tFrame.iFrameStart = 0;
	if (m_tFrame.iFrameStart < 0)
		m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
}

void CETGMenu::Set_Frame(int iStart, int iEnd, int iVertical, DWORD dwSpeed)
{
	m_tFrame.iFrameStart = iStart;
	m_tFrame.iFrameEnd = iEnd;
	m_tFrame.iFrameVetical = iVertical;
	m_tFrame.dwFrameSpeed = dwSpeed;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.iPlus = 1;
}

CETGMenu::CETGMenu()
{
}


CETGMenu::~CETGMenu()
{
}

void CETGMenu::Initiailize()
{
	//for (int i = 0; i < 50; ++i)
	//{
	//	wstring strNum = std::to_wstring(i);
	//	strNum = L"Menu" + strNum;
	//
	//}
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Menu/Menu1.bmp", L"Menu");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Menu/Title.bmp", L"Title");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Menu/Press.bmp", L"Press");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/MapTile/MapTile.bmp", L"MapTile");
	Set_Frame(0, 49, 0, 150);
	CSoundMgr::Get_Instance()->PlayBGM(L"MenuBGM.mp3");
}

void CETGMenu::Update()
{
	if (CKeyMgr::Get_Instance()->KeyDown(VK_RETURN))
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_STAGE);
		//CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_BOSS);
	if (CKeyMgr::Get_Instance()->KeyDown(VK_F12))
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_EDIT);
}

void CETGMenu::LateUpdate()
{
	FrameMove();
}

void CETGMenu::Render(HDC hDC)
{

	//wstring strNum = std::to_wstring(m_tFrame.iFrameStart);
	//strNum = L"Menu" + strNum;
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"Menu");
	//BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	//StretchBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 1024 * (m_tFrame.iFrameStart - 1), 0, 1024 * m_tFrame.iFrameStart, 0, SRCCOPY);
	GdiTransparentBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 1024 * (m_tFrame.iFrameStart - 1), 0, 1024, 640, RGB(255, 0, 255));

	hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"Title");
	GdiTransparentBlt(hDC, WINCX / 2 - 457 / 2, 200, 457, 158, hMemDC, 0, 0, 457, 158, RGB(255, 0, 255));

	hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"Press");
	GdiTransparentBlt(hDC, WINCX / 2 - 400, 550, 800, 76, hMemDC, 0, 0, 800, 76, RGB(255, 0, 255));
}

void CETGMenu::Release()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
}
