#include "stdafx.h"
#include "Radialbullet.h"
#include "GuideBullet.h"

#include "ObjMgr.h"
#include "AbstractFactory.h"

CRadialbullet::CRadialbullet()
{
}


CRadialbullet::~CRadialbullet()
{
	Release();
}

void CRadialbullet::Initialize()
{
	m_eType = BULLET::NORMAL;
	m_tInfo.iCX = 30;
	m_tInfo.iCY = 30;
	m_fSpeed = 3.f;
	m_dwTime = GetTickCount();
	m_pFrameKey = L"NormalBullet";
	m_bRockOn = false;
}

int CRadialbullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	if (m_dwTime + 1000 < GetTickCount())
		m_bDead = true;

	m_tInfo.fX += cosf(DEGREETORADIAN(m_fAngle)) * m_fSpeed;
	m_tInfo.fY -= sinf(DEGREETORADIAN(m_fAngle)) * m_fSpeed;
	return 0;
}

void CRadialbullet::LateUpdate()
{
}

void CRadialbullet::Render(HDC hDC)
{
	CObj::UpdateRect();
	POS tPos = CScrollMgr::Get_MouseScroll();
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(m_pFrameKey);
	GdiTransparentBlt(hDC, SCAST<int>(m_tRect.left + tPos.fX), SCAST<int>(m_tRect.top + tPos.fY), m_tInfo.iCX, m_tInfo.iCY, hMemDC, 0, 0, 14, 14, RGB(255, 0, 255));

}

void CRadialbullet::Release()
{
	for (int i = 0; i < 360; i += 10)
	{
		int RandAngle = rand() % 360;
		CObj* pObj = CAbstractFactory<CGuideBullet>::Create(m_tInfo.fX, m_tInfo.fY, SCAST<float>(i), 1.f, 14, 14);
		CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::M_BULLET);
		pObj->Set_Att(1);
	}
}
