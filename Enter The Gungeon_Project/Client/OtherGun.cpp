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

	if (!m_bLeft)			//플레이어가 오른쪽을 바라볼 때
	{
		switch (m_eGunType)
		{
		case GUN::NORMAL:
			Set_FrameKeyCpy(L"NormalRight");
			//m_pFrameKey = L"NormalRight";
			m_tInfo.iCX = 16;
			m_tInfo.iCY = 24;
			break;
		case GUN::AK:
			Set_FrameKeyCpy(L"AkRight");
			//m_pFrameKey = L"AkRight";
			m_tInfo.iCX = 100;
			m_tInfo.iCY = 100;
			break;
		case GUN::UMP:
			Set_FrameKeyCpy(L"UmpRight");
			//m_pFrameKey = L"UmpRight";
			m_tInfo.iCX = 100;
			m_tInfo.iCY = 100;
			break;
		case GUN::SHOTGUN:
			Set_FrameKeyCpy(L"ShotgunRight");
			//m_pFrameKey = L"ShotgunRight";
			m_tInfo.iCX = 100;
			m_tInfo.iCY = 100;
			break;
		case GUN::RAZER:
			Set_FrameKeyCpy(L"RazerRight");
			//m_pFrameKey = L"RazerRight";
			m_tInfo.iCX = 100;
			m_tInfo.iCY = 100;
			break;
		case GUN::CHARGE:
			Set_FrameKeyCpy(L"ChargeRight");
			//m_pFrameKey = L"ChargeRight";
			m_tInfo.iCX = 100;
			m_tInfo.iCY = 100;
			break;
		default:
			break;
		}
	}
	else if (m_bLeft)		//플레이어가 왼쪽을 바라볼 때
	{
		switch (m_eGunType)
		{
		case GUN::NORMAL:
			Set_FrameKeyCpy(L"NormalLeft");
			//m_pFrameKey = L"NormalLeft";
			m_tInfo.iCX = 16;
			m_tInfo.iCY = 24;
			break;
		case GUN::AK:
			Set_FrameKeyCpy(L"AkLeft");
			//m_pFrameKey = L"";
			m_tInfo.iCX = 100;
			m_tInfo.iCY = 100;
			break;
		case GUN::UMP:
			Set_FrameKeyCpy(L"UmpLeft");
			//m_pFrameKey = L"";
			m_tInfo.iCX = 100;
			m_tInfo.iCY = 100;
			break;
		case GUN::SHOTGUN:
			Set_FrameKeyCpy(L"ShotgunLeft");
			//m_pFrameKey = L"";
			m_tInfo.iCX = 100;
			m_tInfo.iCY = 100;
			break;
		case GUN::RAZER:
			Set_FrameKeyCpy(L"RazerLeft");
			//m_pFrameKey = L"";
			m_tInfo.iCX = 100;
			m_tInfo.iCY = 100;
			break;
		case GUN::CHARGE:
			Set_FrameKeyCpy(L"ChargeLeft");
			//m_pFrameKey = L"";
			m_tInfo.iCX = 100;
			m_tInfo.iCY = 100;
			break;
		default:
			break;
		}
	}

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