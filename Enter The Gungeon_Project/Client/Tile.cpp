#include "stdafx.h"
#include "Tile.h"


CTile::CTile()
{
	m_pFrameKey = L"MapTile";
}


CTile::~CTile()
{
	Release();
}

void CTile::Draw_GuideLine(HDC hDC)
{
	MoveToEx(hDC, (int)(m_tRect.left + CScrollMgr::Get_MouseScroll().fX), (int)(m_tRect.top + CScrollMgr::Get_MouseScroll().fY), nullptr);
	LineTo(hDC, (int)(m_tRect.left + CScrollMgr::Get_MouseScroll().fX), (int)(m_tRect.bottom + CScrollMgr::Get_MouseScroll().fY));
	LineTo(hDC, (int)(m_tRect.right + CScrollMgr::Get_MouseScroll().fX), (int)(m_tRect.bottom + CScrollMgr::Get_MouseScroll().fY));
	LineTo(hDC, (int)(m_tRect.right + CScrollMgr::Get_MouseScroll().fX), (int)(m_tRect.top + CScrollMgr::Get_MouseScroll().fY));
	LineTo(hDC, (int)(m_tRect.left + CScrollMgr::Get_MouseScroll().fX), (int)(m_tRect.top + CScrollMgr::Get_MouseScroll().fY));
}

void CTile::Render(HDC hDC, int iC)
{
	CObj::UpdateRect();
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"MapTileSmall");
	BOOL b = GdiTransparentBlt(hDC, (m_tRect.left) / iC + MAPFIXX, (m_tRect.top) / iC + MAPFIXY,
		8, 8, hMemDC, 8 * m_iDrawID, 0, 8, 8, RGB(255, 0, 255));
	/*BitBlt(hDC, (m_tRect.left + CScrollMgr::Get_MouseScroll().fX) / iC, (m_tRect.top + CScrollMgr::Get_MouseScroll().fY) / iC
		, m_tInfo.iCX / iC, m_tInfo.iCY / iC, hMemDC, m_tInfo.iCX * m_iDrawID, 0, SRCCOPY);*/
}

void CTile::Initialize()
{

	m_tInfo.iCX = TILECX;
	m_tInfo.iCY = TILECY;
	m_iDrawID = 0;
	m_iOption = 1;
}

int CTile::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	return OBJ_NOEVENT;
}

void CTile::LateUpdate()
{
}

void CTile::Render(HDC hDC)
{
	if (m_iDrawID == 0)
		return;
	CObj::UpdateRect();
	m_tRect;
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(m_pFrameKey);
	BitBlt(hDC, (int)(m_tRect.left + CScrollMgr::Get_MouseScroll().fX), (int)(m_tRect.top + CScrollMgr::Get_MouseScroll().fY)
		, m_tInfo.iCX, m_tInfo.iCY, hMemDC, m_tInfo.iCX * m_iDrawID, 0, SRCCOPY);
#ifdef _DEBUG

	
#endif
}

void CTile::Release()
{
}
