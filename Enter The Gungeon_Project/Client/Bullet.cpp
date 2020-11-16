#include "stdafx.h"
#include "Bullet.h"

#include "ScrollMgr.h"

CBullet::CBullet()
{
}

CBullet::CBullet(float fx, float fy)
{
	m_tInfo.fX = fx;
	m_tInfo.fY = fy;
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
}

int CBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	return OBJ_NOEVENT;
}

void CBullet::LateUpdate()
{
}

void CBullet::Render(HDC hDC)
{
	CObj::UpdateRect();
	POS tPos = CScrollMgr::Get_MouseScroll();
	Ellipse(hDC, SCAST<int>(m_tRect.left + tPos.fX), SCAST<int>(m_tRect.top + tPos.fY), SCAST<int>(m_tRect.right + tPos.fX), SCAST<int>(m_tRect.bottom + tPos.fY));
}

void CBullet::Release()
{
}
