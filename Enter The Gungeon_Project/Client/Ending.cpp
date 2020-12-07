#include "stdafx.h"
#include "Ending.h"

#include "KeyMgr.h"
#include "NetWork.h"

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
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(255, 255, 255));
	HFONT hFont = CreateFont(12, 0, 0, 0, FW_NORMAL, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("µÕ±Ù¸ð²Ã"));
	HFONT oldFont = (HFONT)SelectObject(hDC, hFont);
	TCHAR tValue[32] = L"";
	if (CNetwork::GetInstance()->m_iWin == 1)
		swprintf_s(tValue, L"WIN");
	else if (CNetwork::GetInstance()->m_iWin == -1)
		swprintf_s(tValue, L"LOSE");

	TextOut(hDC, WINCX - 80, WINCY - 50, tValue, lstrlen(tValue));
}

void CEnding::Release()
{
	MCIWndClose(m_hVideo);
}
