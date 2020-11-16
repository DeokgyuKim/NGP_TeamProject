#include "stdafx.h"
#include "Boom.h"


CBoom::CBoom()
{
}


CBoom::~CBoom()
{
}

void CBoom::Initialize()
{
	m_tInfo.iCX = 256;
	m_tInfo.iCY = 256;
	m_dwTime = GetTickCount();
	m_iAtt = 1;
	m_pFrameKey = L"MonsterDie2";
	Set_Frame(0, 8, 0, 62);
	Set_Frame_Plus(true);
	m_bDead = false;
}

int CBoom::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	if (m_dwTime + 500 < GetTickCount())
		m_bDead = true;
	return OBJ_NOEVENT;
}

void CBoom::LateUpdate()
{
	CObj::FrameMove();
}

void CBoom::Render(HDC hDC)
{
	CObj::UpdateRect();
	POS tPos = CScrollMgr::Get_MouseScroll();
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(m_pFrameKey);
	BOOL b = GdiTransparentBlt(hDC, SCAST<int>(m_tRect.left + tPos.fX), SCAST<int>(m_tRect.top + tPos.fY), m_tInfo.iCX, m_tInfo.iCY, hMemDC, m_tInfo.iCX * m_tFrame.iFrameStart, m_tInfo.iCY * m_tFrame.iFrameVetical, m_tInfo.iCX, m_tInfo.iCY, RGB(255, 0, 255));
}

void CBoom::Release()
{
}
