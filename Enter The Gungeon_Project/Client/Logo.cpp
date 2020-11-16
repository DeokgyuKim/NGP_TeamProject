#include "stdafx.h"
#include "Logo.h"

#include "BmpMgr.h"
#include "SceneMgr.h"


CLogo::CLogo()
{
}


CLogo::~CLogo()
{
}

void CLogo::Initiailize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Logo/Logo.bmp", L"Logo");
	m_dwTime = GetTickCount();
}

void CLogo::Update()
{
	if (m_dwTime + 2000 < GetTickCount())
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_INTRO);
}

void CLogo::LateUpdate()
{
}

void CLogo::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"Logo");
	BOOL b = BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void CLogo::Release()
{
}
