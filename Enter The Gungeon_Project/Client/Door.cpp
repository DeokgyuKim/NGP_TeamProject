#include "stdafx.h"
#include "Door.h"

#include "TileMgr.h"

CDoor::CDoor()
{
}


CDoor::~CDoor()
{
}

void CDoor::Set_Open()
{
	if (m_bOpen)
		return;
	m_bOpen = true;
	Set_Frame(0, 2, 0, 150);
	Set_Frame_Plus(true);
	//지나갈수있게
	CTileMgr::Get_Instance()->Set_TileOption(m_iPosX, m_iPosY, 0);
	switch (m_eType)
	{
	case DOOR::LEFT:
	case DOOR::RIGHT:
		CTileMgr::Get_Instance()->Set_TileOption(m_iPosX, m_iPosY + 1, 0);
		break;
	case DOOR::TOP:
	case DOOR::BOTTOM:
		CTileMgr::Get_Instance()->Set_TileOption(m_iPosX + 1, m_iPosY, 0);
		break;
	default:
		break;
	}
}

void CDoor::Set_Close()
{
	if (!m_bOpen)
		return;
	m_bOpen = false;
	Set_Frame(0, 2, 0, 150);
	Set_Frame_Plus(true);
	//지나갈수없게
	CTileMgr::Get_Instance()->Set_TileOption(m_iPosX, m_iPosY, 1);
	switch (m_eType)
	{
	case DOOR::LEFT:
	case DOOR::RIGHT:
		CTileMgr::Get_Instance()->Set_TileOption(m_iPosX, m_iPosY + 1, 1);
		break;
	case DOOR::TOP:
	case DOOR::BOTTOM:
		CTileMgr::Get_Instance()->Set_TileOption(m_iPosX + 1, m_iPosY, 1);
		break;
	default:
		break;
	}
}

void CDoor::Initialize()
{
	m_bDead = false;
	m_bOpen = true;
	Set_Frame(0, 2, 0, 150);
	Set_Frame_Plus(true);
}

int CDoor::Update()
{
	if (m_bOpen)
	{
		if (m_tFrame.iFrameStart < m_tFrame.iFrameEnd)
		{
			FrameMove();
		}
	}
	return 0;
}

void CDoor::LateUpdate()
{
}

void CDoor::Render(HDC hDC)
{
	CObj::UpdateRect();
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(m_pFrameKey);
	POS tPos = CScrollMgr::Get_MouseScroll();
	BOOL b;
	switch (m_eType)
	{
	case DOOR::LEFT:
	case DOOR::RIGHT:
		b = GdiTransparentBlt(hDC, (int)(m_tRect.left + tPos.fX), (int)(m_tRect.top + tPos.fY),
			m_tInfo.iCX, m_tInfo.iCY, hMemDC, m_tInfo.iCX * m_tFrame.iFrameStart, 0, m_tInfo.iCX, m_tInfo.iCY, RGB(255, 0, 255));
		break;
	case DOOR::TOP:
	case DOOR::BOTTOM:
		b = GdiTransparentBlt(hDC, (int)(m_tRect.left + tPos.fX), (int)(m_tRect.top + tPos.fY), 
			m_tInfo.iCX, m_tInfo.iCY, hMemDC, 0, m_tInfo.iCY * m_tFrame.iFrameStart, m_tInfo.iCX, m_tInfo.iCY, RGB(255, 0, 255));
		break;
	default:
		break;
	}
}

void CDoor::Release()
{
}
