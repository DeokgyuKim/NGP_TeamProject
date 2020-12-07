#include "stdafx.h"
#include "OtherGun.h"
#include "AngleBullet.h"

#include "ObjMgr.h"
#include "KeyMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"

#include "NetWork.h"

COtherGun::COtherGun()
{
}


COtherGun::~COtherGun()
{
}

void COtherGun::Initialize()
{	
	m_tInfo.iCX = 20;
	m_tInfo.iCY = 20;
	m_fSpeed = 10.f;
	m_fAngle = 0.f;
	m_dwTime[GUN::END] = {};
	m_iTime[GUN::RATEOFFIRE] = 200;
	m_iTime[GUN::RELOAD] = 1000;
	m_iBullet[BULLET::COUNT_MAX] = 5;
	m_iBullet[BULLET::COUNT_NOW] = m_iBullet[BULLET::COUNT_MAX];
	m_bReload = false;
	m_bSelling = false;
	m_iRenderCount = 0;

	m_pFrameKey = new TCHAR[30];
}

int COtherGun::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void COtherGun::LateUpdate()
{
}

void COtherGun::Render(HDC hDC)
{
	CObj::UpdateRect();
	POS tScorll = CScrollMgr::Get_MouseScroll();
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(m_pFrameKey);

	BOOL b = GdiTransparentBlt(hDC, (int)(m_tRect.left + tScorll.fX), (int)(m_tRect.top + tScorll.fY), m_tInfo.iCX, m_tInfo.iCY,
		hMemDC, m_tInfo.iCX * m_iRenderCount, 0, m_tInfo.iCX, m_tInfo.iCY, RGB(255, 255, 255));

}

void COtherGun::Release()
{
	delete[] m_pFrameKey;
}