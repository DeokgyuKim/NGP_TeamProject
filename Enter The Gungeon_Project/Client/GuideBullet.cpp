#include "stdafx.h"
#include "GuideBullet.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"

CGuideBullet::CGuideBullet()
{
}


CGuideBullet::~CGuideBullet()
{
	Release();
}

void CGuideBullet::Initialize()
{
	m_tInfo.iCX = 14; 
	m_tInfo.iCY = 14; 
	m_fSpeed = 10.f; 
	m_bLockOn = false;
	m_dwTime = GetTickCount();
	m_pFrameKey = L"NormalBullet";
	m_dwDead = GetTickCount();
}

int CGuideBullet::Update()
{
	if (m_bDead || m_dwDead + 10000 < GetTickCount())
		return OBJ_DEAD;
	if (m_dwTime + 1000 < GetTickCount())
	{
		m_bLockOn = true;
		m_dwTime = LONG_MAX;
	}
	if (m_bLockOn)
	{
		CObj* pTarget = CObjMgr::Get_Instance()->Get_Target(this, OBJ::PLAYER);
		if (nullptr == pTarget)
			return OBJ_DEAD;
		float x = pTarget->Get_Info()->fX - m_tInfo.fX;
		float y = pTarget->Get_Info()->fY - m_tInfo.fY;
		float fDist = sqrtf(x * x + y * y);
		m_fAngle = acosf(x / fDist);

		if (pTarget->Get_Info()->fY > m_tInfo.fY)
			m_fAngle *= -1.f;
		m_bLockOn = false;
	}

	m_fSpeed += 0.1f;
	m_tInfo.fX += cosf((m_fAngle)) * m_fSpeed; 
	m_tInfo.fY -= sinf((m_fAngle)) * m_fSpeed;

	return OBJ_NOEVENT; 
}

void CGuideBullet::LateUpdate()
{
}

void CGuideBullet::Render(HDC hDC)
{
	CObj::UpdateRect(); 
	POS tPos = CScrollMgr::Get_Scroll();
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(m_pFrameKey);
	GdiTransparentBlt(hDC, SCAST<int>(m_tRect.left + tPos.fX), SCAST<int>(m_tRect.top + tPos.fY), m_tInfo.iCX, m_tInfo.iCY, hMemDC, 0, 0, 14, 14, RGB(255, 0, 255));
}

void CGuideBullet::Release()
{
	CEffectMgr::MakeEffect(L"BulletDieEffect", FRAME{ 0, 6, 0, 1, 100, 0 }, m_tInfo.fX, m_tInfo.fY, 27, 27);
}
