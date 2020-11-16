#include "stdafx.h"
#include "Effect.h"


CEffect::CEffect()
{
}


CEffect::~CEffect()
{
	Release();
}

void CEffect::Initialize()
{
	m_bFinish = true;
}

int CEffect::Update()
{
	if (!m_bFinish)
		return OBJ_DEAD;
	return 0;
}

void CEffect::LateUpdate()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		m_tFrame.iFrameStart += m_tFrame.iPlus;
		m_tFrame.dwFrameTime = GetTickCount();
	}
	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		m_tInfo.iCY = 9999;
	}
}

void CEffect::Render(HDC hDC)
{
	CObj::UpdateRect();
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(m_pFrameKey);
	POS tPos = CScrollMgr::Get_MouseScroll();

	m_bFinish = GdiTransparentBlt(hDC, SCAST<int>(m_tInfo.fX - m_tInfo.iCX * m_iSize / 2 + tPos.fX), SCAST<int>(m_tInfo.fY - m_tInfo.iCX * m_iSize / 2 + tPos.fY), m_tInfo.iCX * m_iSize, m_tInfo.iCY * m_iSize, hMemDC, m_tInfo.iCX * m_tFrame.iFrameStart, m_tInfo.iCY * m_tFrame.iFrameVetical, m_tInfo.iCX, m_tInfo.iCY, RGB(255, 0, 255));
}

void CEffect::Release()
{
}
