#include "stdafx.h"
#include "ScrewBullet.h"


CScrewBullet::CScrewBullet()
{
}


CScrewBullet::~CScrewBullet()
{
}

void CScrewBullet::Initialize()
{
	m_bIsInit = false;
	m_tInfo.iCX = 30; 
	m_tInfo.iCY = 30; 
	m_fSpeed = 2.f; 
	m_fRotAngle = 0.f; 
	m_fRotDist = 15.f; 
	m_fRotSpeed = 10.f; 
}

int CScrewBullet::Update()
{
	if (!m_bIsInit)
	{
		m_tCenter.x = LONG(m_tInfo.fX); 
		m_tCenter.y = LONG(m_tInfo.fY);
		m_bIsInit = true; 
	}
	m_tCenter.x += LONG(cosf(m_fAngle * PI / 180.f) * m_fSpeed);
	m_tCenter.y -= LONG(sinf(m_fAngle * PI / 180.f) * m_fSpeed);
	
	m_fRotAngle += m_fRotSpeed;
	m_tInfo.fX = m_tCenter.x + cosf(m_fRotAngle * PI / 180.f) * m_fRotDist;
	m_tInfo.fY = m_tCenter.y - sinf(m_fRotAngle * PI / 180.f) * m_fRotDist;
	return 0;
}

void CScrewBullet::LateUpdate()
{
}

void CScrewBullet::Render(HDC hDC)
{
	CObj::UpdateRect(); 
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CScrewBullet::Release()
{
}
