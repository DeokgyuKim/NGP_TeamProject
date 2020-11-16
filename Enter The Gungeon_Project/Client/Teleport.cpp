#include "stdafx.h"
#include "Teleport.h"

#define MAPVALUE 8


void CTeleport::RenderMap(HDC hDC, int iC)
{
	CObj::UpdateRect();
	HDC hMemDC = NULL;
	if(m_bOn)
		hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"TeleportTile");
	else
		hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"TeleportOffTile");
		
	GdiTransparentBlt(hDC, (int)(m_tInfo.fX / iC + MAPFIXX - m_tInfo.iCX / 8), (int)(m_tInfo.fY / iC + MAPFIXY - m_tInfo.iCY / 8)
		, m_tInfo.iCX / 4, m_tInfo.iCY / 4, hMemDC, 0, 0, m_tInfo.iCX, m_tInfo.iCY, RGB(255, 0, 255));
}

CTeleport::CTeleport()
{
}


CTeleport::~CTeleport()
{
}

void CTeleport::Initialize()
{
	m_tInfo.iCX = 64;
	m_tInfo.iCY = 64;
	m_bOn = false;
	Set_Frame(0, 11, 0, 100);
	Set_Frame_Plus(true);
	Set_FrameKey(L"TwinkleTile");
	
}

int CTeleport::Update()
{
	m_tCollisionRect.left =		(LONG)(m_tInfo.fX / MAPVALUE + MAPFIXX - m_tInfo.iCX / MAPVALUE);
	m_tCollisionRect.top =		(LONG)(m_tInfo.fY / MAPVALUE + MAPFIXY - m_tInfo.iCY / MAPVALUE);
	m_tCollisionRect.right =	(LONG)(m_tCollisionRect.left + m_tInfo.iCX / (MAPVALUE / 2));
	m_tCollisionRect.bottom =	(LONG)(m_tCollisionRect.top + m_tInfo.iCY / (MAPVALUE / 2));
	return 0;
}

void CTeleport::LateUpdate()
{
	if(m_bOn)
		CObj::FrameMove();
}

void CTeleport::Render(HDC hDC)
{
	CObj::UpdateRect();
	POS tPos = CScrollMgr::Get_MouseScroll();
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(m_pFrameKey);
	BitBlt(hDC, (int)(m_tRect.left + tPos.fX), (int)(m_tRect.top + tPos.fY), m_tInfo.iCX, m_tInfo.iCY, hMemDC, m_tInfo.iCX * m_tFrame.iFrameStart, 0, SRCCOPY);
}

void CTeleport::Release()
{
}
