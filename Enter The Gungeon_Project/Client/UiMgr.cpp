#include "stdafx.h"
#include "UiMgr.h"
#include "Player.h"
#include "Gun.h"

#include "ObjMgr.h"
#include "TileMgr.h"

CUiMgr* CUiMgr::m_pInstance = NULL;
void CUiMgr::Render(HDC hDC)
{
	HDC hMemDC = nullptr;
	TCHAR tTemp[32] = {};
	

	if (m_pBoss == NULL)
		m_pBoss = CObjMgr::Get_Instance()->Get_Boss();

	int iFullCount = 0;
	int iHalfCount = 0;
	iFullCount = m_pPlayer->Get_Hp() >> 1;
	if ((m_pPlayer->Get_Hp() & 1) == 1)
		iHalfCount = 1;
	
	int i = 0;
	hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"HPFullUI");
		//BitBlt(hDC, 30 + 50 * i, 30, 45, 39, hMemDC, 0, 0, SRCCOPY);
	for (i = 0; i < iFullCount; ++i)
		GdiTransparentBlt(hDC, 30 + 50 * i, 30 , 45, 39, hMemDC, 0, 0, 45, 39, RGB(255, 0, 255));
	if (iHalfCount != 0)
	{
		hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"HPHalfUI");
		GdiTransparentBlt(hDC, 30 + 50 * iFullCount, 30, 45, 39, hMemDC, 0, 0, 45, 39, RGB(255, 0, 255));
		//BitBlt(hDC, 30 + 50 * (iFullCount), 30, 45, 39, hMemDC, 0, 0, SRCCOPY);
	}


	/*swprintf_s(tTemp, L"HP: %d", m_pPlayer->Get_Hp());
	TextOut(hDC, 30, 30, tTemp, lstrlen(tTemp));*/

	/*swprintf_s(tTemp, L"Shield: %d", CAST<CPlayer*>(m_pPlayer)->Get_Shield());
	TextOut(hDC, 30, 50, tTemp, lstrlen(tTemp));*/
	hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"Dreadshot");
	for (i = 0; i < CAST<CPlayer*>(m_pPlayer)->Get_Dreadshot(); ++i)
		GdiTransparentBlt(hDC, 30 + 40 * i, 80, 36, 36, hMemDC, 0, 0, 36, 36, RGB(255, 0, 255));
		//BitBlt(hDC, 30 + 40 * i, 70, 45, 39, hMemDC, 0, 0, SRCCOPY);
	
	/*swprintf_s(tTemp, L"Dreadshot: %d", CAST<CPlayer*>(m_pPlayer)->Get_Dreadshot());
	TextOut(hDC, 30, 70, tTemp, lstrlen(tTemp));*/

	CObj* pObj = CAST<CPlayer*>(m_pPlayer)->Get_GunNow();

	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(255, 255, 255));
	HFONT hFont = CreateFont(12, 0, 0, 0, FW_NORMAL, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("둥근모꼴"));
	HFONT oldFont = (HFONT)SelectObject(hDC, hFont);
	TCHAR tValue[32] = L"";
	if (CAST<CGun*>(pObj)->Get_BulletState()[BULLET::COUNT_ALL_MAX] == 0)
		swprintf_s(tValue, L"무한");
	else
		swprintf_s(tValue, L"%d / %d", CAST<CGun*>(pObj)->Get_BulletState()[BULLET::COUNT_ALL_NOW],
			CAST<CGun*>(pObj)->Get_BulletState()[BULLET::COUNT_ALL_MAX]);
	TextOut(hDC, WINCX - 80, WINCY - 50, tValue, lstrlen(tValue));

	

	
	/*swprintf_s(tValue, L"%d", m_iSell[0] * m_iValue);
	TextOut(hDC, m_tRect.left + 244 + tPos.fX, m_tRect.top + 342 + tPos.fY, tValue, lstrlen(tValue));
	swprintf_s(tValue, L"%d", m_iSell[1] * m_iValue);
	TextOut(hDC, m_tRect.left + 565 + tPos.fX, m_tRect.top + 342 + tPos.fY, tValue, lstrlen(tValue));
	swprintf_s(tValue, L"%d", m_iSell[2] * m_iValue);
	TextOut(hDC, m_tRect.left + 708 + tPos.fX, m_tRect.top + 118 + tPos.fY, tValue, lstrlen(tValue));
	swprintf_s(tValue, L"%d", m_iSell[3] * m_iValue);
	TextOut(hDC, m_tRect.left + 708 + tPos.fX, m_tRect.top + 208 + tPos.fY, tValue, lstrlen(tValue));*/

	//244 342
	SelectObject(hDC, oldFont);
	DeleteObject(hFont);

	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(255, 255, 255));
	hFont = CreateFont(20, 0, 0, 0, FW_NORMAL, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("둥근모꼴"));
	oldFont = (HFONT)SelectObject(hDC, hFont);

	swprintf_s(tValue, L"GOLD %d", m_pPlayer->Get_Gold());
	TextOut(hDC, 30, 150, tValue, lstrlen(tValue));

	SelectObject(hDC, oldFont);
	DeleteObject(hFont);

	
	//if(CAST<CGun*>(pObj)->Get_BulletState()[BULLET::COUNT_ALL_MAX] == 0)
	//	swprintf_s(tTemp, L"무한");
	//else
	//	swprintf_s(tTemp, L"%d / %d", CAST<CGun*>(pObj)->Get_BulletState()[BULLET::COUNT_ALL_NOW], 
	//		CAST<CGun*>(pObj)->Get_BulletState()[BULLET::COUNT_ALL_MAX]);
	//TextOut(hDC, WINCX - 80, WINCY - 50, tTemp, lstrlen(tTemp));

	if (CAST<CGun*>(pObj)->Get_Reload())
	{
		POS tPos = CScrollMgr::Get_MouseScroll();
		hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"ReloadingBar");
		GdiTransparentBlt(hDC, SCAST<int>(m_pPlayer->Get_Info()->fX - 32 + tPos.fX), SCAST<int>(m_pPlayer->Get_Info()->fY - m_pPlayer->Get_Info()->iCY / 2 - 20 + tPos.fY)
			, 64, 13, hMemDC, 0, 0, 64, 13, RGB(255, 0, 255));
		hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"ReloadingStick");
		float fX = CAST<CGun*>(CAST<CPlayer*>(m_pPlayer)->Get_GunNow())->Get_ReloadTime();
		GdiTransparentBlt(hDC, SCAST<int>(m_pPlayer->Get_Info()->fX - 21 + tPos.fX + (42 * fX)), SCAST<int>(m_pPlayer->Get_Info()->fY - m_pPlayer->Get_Info()->iCY / 2 - 20 + tPos.fY)
			, 5, 13, hMemDC, 0, 0, 5, 13, RGB(255, 0, 255));
		//swprintf_s(tTemp, L"장전중");
		//TextOut(hDC, WINCX - 80, WINCY - 30, tTemp, lstrlen(tTemp));
	}
	hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"RemainingBulletZeroUI");
	GdiTransparentBlt(hDC, WINCX - 19, WINCY - 28, 16, 10, hMemDC, 0, 0, 16, 10, RGB(255, 0, 255));
	//BitBlt(hDC, WINCX - 19, WINCY - 28, 16, 10, hMemDC, 0, 0, SRCCOPY);
	for (int i = 0; i < CAST<CGun*>(pObj)->Get_BulletState()[BULLET::COUNT_NOW]; ++i)
	{
		RECT rc = { WINCX - 20, WINCY - 14 * i - 40, WINCX - 10, WINCY - 12 * i - 40 };
		if(CAST<CGun*>(CAST<CPlayer*>(m_pPlayer)->Get_GunNow())->Get_GunType() == GUN::NORMAL||
			CAST<CGun*>(CAST<CPlayer*>(m_pPlayer)->Get_GunNow())->Get_GunType() == GUN::AK ||
			CAST<CGun*>(CAST<CPlayer*>(m_pPlayer)->Get_GunNow())->Get_GunType() == GUN::UMP)
			hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"NormalBulletUI");
		else if(CAST<CGun*>(CAST<CPlayer*>(m_pPlayer)->Get_GunNow())->Get_GunType() == GUN::RAZER ||
			CAST<CGun*>(CAST<CPlayer*>(m_pPlayer)->Get_GunNow())->Get_GunType() == GUN::CHARGE)
			hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"BlueBulletUI");
		else if (CAST<CGun*>(CAST<CPlayer*>(m_pPlayer)->Get_GunNow())->Get_GunType() == GUN::SHOTGUN)
			hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"RedBulletUI");
		GdiTransparentBlt(hDC, rc.left, rc.top, 18, 12, hMemDC, 0, 0, 18, 12, RGB(255, 0, 255));

		//BitBlt(hDC, rc.left, rc.top, 18, 12, hMemDC, 0, 0, SRCCOPY);
		//Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);
	}
	hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"RemainingBulletMaxUI");
	GdiTransparentBlt(hDC, WINCX - 19, WINCY - 14 * CAST<CGun*>(pObj)->Get_BulletState()[BULLET::COUNT_NOW] - 40, 16, 10, hMemDC, 0, 0, 16, 10, RGB(255, 0, 255));

	//보스 UI
	if (m_pBoss != NULL)
	{
		HDC hFrameDC = CBmpMgr::Get_Instance()->Get_MemDC(L"BossHPFrameUI");
		//HDC hFrameBack = CBmpMgr::Get_Instance()->Get_MemDC(L"BossHPFrameUIBack");
		//BitBlt(hFrameDC, 0, 0, 603, 39, hFrameBack, 0, 0, SRCCOPY);
		HDC hBarDC = CBmpMgr::Get_Instance()->Get_MemDC(L"BossHPBar");
		int iHp = m_pBoss->Get_Hp();
		GdiTransparentBlt(hDC, WINCX / 2 - 301, WINCY - 100, 603, 39, hFrameDC, 0, 0, 603, 39, RGB(255, 0, 255));
		GdiTransparentBlt(hDC, WINCX / 2 - 301 + 51, WINCY - 100 + 9, m_pBoss->Get_Hp(), 23, hBarDC, 0, 0, m_pBoss->Get_Hp(), 23, RGB(255, 0, 255));
	}

	//미니맵
	//HDC hFrame = CBmpMgr::Get_Instance()->Get_MemDC(L"MinimapFrameUI");
	if (m_pBoss == NULL)
	{
		HDC hBoard = CBmpMgr::Get_Instance()->Get_MemDC(L"BigMapSec");
		HDC hBoardBack = CBmpMgr::Get_Instance()->Get_MemDC(L"BigMapSecBack");
		BitBlt(hBoard, 0, 0, 1920, 1200, hBoardBack, 0, 0, SRCCOPY);
		//BitBlt(hFrame, 3, 3, 160, 120, hBoard, 0, 0, SRCCOPY);
		HDC hPlayerUi = CBmpMgr::Get_Instance()->Get_MemDC(L"PlayerMapUI");
		CTileMgr::Get_Instance()->Render(hBoard, 1);
		GdiTransparentBlt(hBoard, (int)(m_pPlayer->Get_Info()->fX + CScrollMgr::Get_MouseScroll().fX - 80), (int)(m_pPlayer->Get_Info()->fY + CScrollMgr::Get_MouseScroll().fY - 80),
			160, 160, hPlayerUi, 0, 0, 40, 40, RGB(255, 0, 255));

		HDC hFrame = CBmpMgr::Get_Instance()->Get_MemDC(L"MinimapFrameUI");
		HDC hFrameBoard = CBmpMgr::Get_Instance()->Get_MemDC(L"MinimapBoardUI");

		BitBlt(hFrame, 3, 3, 200, 140, hFrameBoard, 0, 0, SRCCOPY);

		GdiTransparentBlt(hFrame, 3, 3, 200, 140, hBoard, 0, 0, 1920, 1200, RGB(255, 0, 255));

		GdiTransparentBlt(hDC, WINCX - 200, 0, 200, 140, hFrame, 0, 0, 200, 140, RGB(255, 0, 255));
	}
	


	//BitBlt(hDC, WINCX - 19, WINCY - 14 * CAST<CGun*>(pObj)->Get_BulletState()[BULLET::COUNT_NOW] - 40, 16, 10, hMemDC, 0, 0, SRCCOPY);
}

CUiMgr::CUiMgr()
{
	m_bMapOn = true; 
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	m_pBoss = NULL;
}
