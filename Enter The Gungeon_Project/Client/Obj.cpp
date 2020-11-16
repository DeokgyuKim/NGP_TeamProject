#include "stdafx.h"
#include "Obj.h"
//#include "ScrollMgr.h"


CObj::CObj()
	:m_fSpeed(0.f)
	,m_bDead(false)
	,m_fAngle(0.f)
{
	ZeroMemory(&m_tInfo, sizeof(INFO)); 
	ZeroMemory(&m_tRect, sizeof(RECT));
}


CObj::~CObj()
{
}

void CObj::UpdateRect()
{
	m_tRect.left	= LONG(m_tInfo.fX - m_tInfo.iCX / 2);
	m_tRect.top		= LONG(m_tInfo.fY - m_tInfo.iCY * 0.5f);
	m_tRect.right	= LONG(m_tInfo.fX + (m_tInfo.iCX >> 1));
	m_tRect.bottom	= LONG(m_tInfo.fY + (m_tInfo.iCY >> 1));
}

void CObj::FrameMove()
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
