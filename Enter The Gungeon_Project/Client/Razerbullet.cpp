#include "stdafx.h"
#include "Razerbullet.h"


CRazerbullet::CRazerbullet()
{
}


CRazerbullet::~CRazerbullet()
{
}

void CRazerbullet::Initialize()
{
	m_hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"RazerBullet");
	m_eType = BULLET::RAZER;
	m_bCheck = true;
	m_tInfo.iCX = 1;
	m_tInfo.iCY = 1;
	m_iAtt = 10;
	m_dwTime = 0;
}

int CRazerbullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	
	
	if (m_bCheck)
	{
		if (m_dwTime + 10 < GetTickCount())
		{
			m_tInfo.iCX += 2;
			m_tInfo.iCY += 2;
			if (m_tInfo.iCX >= 30)
				m_bCheck = false;
			m_dwTime = GetTickCount();
		}
	}
	else
	{
		if (m_dwTime + 10 < GetTickCount())
		{
			--m_tInfo.iCX;
			--m_tInfo.iCY;
			if (m_tInfo.iCX <= 4)
				return OBJ_DEAD;
			m_dwTime = GetTickCount();
		}
	}
	return OBJ_NOEVENT;
}

void CRazerbullet::LateUpdate()
{
}

void CRazerbullet::Render(HDC hDC)
{
	CObj::UpdateRect();
	POS tPos = CScrollMgr::Get_MouseScroll();
	GdiTransparentBlt(hDC, SCAST<int>(m_tRect.left + tPos.fX), SCAST<int>(m_tRect.top + tPos.fY), m_tInfo.iCX, m_tInfo.iCY, m_hMemDC, 0, 0, 14, 14, RGB(255, 0, 255));
}

void CRazerbullet::Release()
{
	CEffectMgr::MakeEffect(L"BulletDieEffect", FRAME{ 0, 6, 0, 1, 100, 0 }, m_tInfo.fX, m_tInfo.fY, 27, 27);
}
