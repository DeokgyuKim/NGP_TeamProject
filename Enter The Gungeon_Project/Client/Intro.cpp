#include "stdafx.h"
#include "Intro.h"

#include "KeyMgr.h"
#include "SceneMgr.h"


CIntro::CIntro()
{
}


CIntro::~CIntro()
{
	Release();
}

void CIntro::Initiailize()
{
	m_hVideo = MCIWndCreate(g_hWND, nullptr, WS_VISIBLE | WS_CHILD | MCIWNDF_NOPLAYBAR, L"../Resource/Image/Logo/Intro.wmv");
	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);
	MCIWndPlay(m_hVideo);
}

void CIntro::Update()
{
}

void CIntro::LateUpdate()
{
	if (CKeyMgr::Get_Instance()->KeyDown(VK_RETURN) || MCIWndGetPosition(m_hVideo) >= MCIWndGetLength(m_hVideo))
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_MENU);
}

void CIntro::Render(HDC hDC)
{
}

void CIntro::Release()
{
	MCIWndClose(m_hVideo);
}
