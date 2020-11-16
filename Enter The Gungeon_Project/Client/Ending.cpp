#include "stdafx.h"
#include "Ending.h"

#include "KeyMgr.h"

CEnding::CEnding()
{
}


CEnding::~CEnding()
{
}

void CEnding::Initiailize()
{
	m_hVideo = MCIWndCreate(g_hWND, nullptr, WS_VISIBLE | WS_CHILD | MCIWNDF_NOPLAYBAR, L"../Resource/Image/Logo/Ending.wmv");
	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);
	MCIWndPlay(m_hVideo);
}

void CEnding::Update()
{
}

void CEnding::LateUpdate()
{
	if (CKeyMgr::Get_Instance()->KeyDown(VK_RETURN) || MCIWndGetPosition(m_hVideo) >= MCIWndGetLength(m_hVideo))
		DestroyWindow(g_hWND);
}

void CEnding::Render(HDC hDC)
{
}

void CEnding::Release()
{
	MCIWndClose(m_hVideo);
}
