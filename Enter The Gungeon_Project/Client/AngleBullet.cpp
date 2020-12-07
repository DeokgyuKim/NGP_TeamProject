#include "stdafx.h"
#include "AngleBullet.h"
#include "ScrollMgr.h"

CAngleBullet::CAngleBullet()
{
}


CAngleBullet::~CAngleBullet()
{
	Release();
}

void CAngleBullet::Initialize()
{

	m_dwTime = GetTickCount();
	m_hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"NormalBullet");
	m_eType = BULLET::NORMAL;
	m_bMove = true;
}

int CAngleBullet::Update()
{
	if (m_bDead || m_dwTime + 10000 < GetTickCount())
		return OBJ_DEAD;
	if (m_bMove == false)
		return OBJ_NOEVENT;
	m_tInfo.fX += cosf(DEGREETORADIAN(m_fAngle)) * m_fSpeed;
	m_tInfo.fY -= sinf(DEGREETORADIAN(m_fAngle)) * m_fSpeed;
	return 0;
}

void CAngleBullet::LateUpdate()
{
}

void CAngleBullet::Render(HDC hDC)
{
	CObj::UpdateRect();
	POS tPos = CScrollMgr::Get_MouseScroll();
	GdiTransparentBlt(hDC, SCAST<int>(m_tRect.left + tPos.fX), SCAST<int>(m_tRect.top + tPos.fY), m_tInfo.iCX, m_tInfo.iCY, m_hMemDC, 0, 0, 14, 14, RGB(255, 0, 255));
	//Ellipse(hDC, SCAST<int>(m_tRect.left + tPos.fX), SCAST<int>(m_tRect.top + tPos.fY), SCAST<int>(m_tRect.right + tPos.fX), SCAST<int>(m_tRect.bottom + tPos.fY));
}

void CAngleBullet::Release()
{
	CEffectMgr::MakeEffect(L"BulletDieEffect", FRAME{ 0, 6, 0, 1, 100, 0 }, m_tInfo.fX, m_tInfo.fY, 27, 27, m_tInfo.iCX / 14);
}
