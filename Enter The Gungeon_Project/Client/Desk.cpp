#include "stdafx.h"
#include "Desk.h"

#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"


CDesk::CDesk()
{
}


CDesk::~CDesk()
{
}

void CDesk::UpdateCollisionRect()
{
	m_tRectCollision[DIR::LEFT].left = SCAST<LONG>(m_tInfo.fX - 128);
	m_tRectCollision[DIR::LEFT].right = SCAST<LONG>(m_tInfo.fX - 64);
	m_tRectCollision[DIR::LEFT].top = SCAST<LONG>(m_tInfo.fY - 32);
	m_tRectCollision[DIR::LEFT].bottom = SCAST<LONG>(m_tInfo.fY + 32);

	m_tRectCollision[DIR::RIGHT].left = SCAST<LONG>(m_tInfo.fX + 64);
	m_tRectCollision[DIR::RIGHT].right = SCAST<LONG>(m_tInfo.fX + 128);
	m_tRectCollision[DIR::RIGHT].top = SCAST<LONG>(m_tInfo.fY - 32);
	m_tRectCollision[DIR::RIGHT].bottom = SCAST<LONG>(m_tInfo.fY + 32);

	m_tRectCollision[DIR::TOP].left = SCAST<LONG>(m_tInfo.fX - 32);
	m_tRectCollision[DIR::TOP].right = SCAST<LONG>(m_tInfo.fX + 32);
	m_tRectCollision[DIR::TOP].top = SCAST<LONG>(m_tInfo.fY - 128);
	m_tRectCollision[DIR::TOP].bottom = SCAST<LONG>(m_tInfo.fY - 64);

	m_tRectCollision[DIR::BOTTOM].left = SCAST<LONG>(m_tInfo.fX - 32);
	m_tRectCollision[DIR::BOTTOM].right = SCAST<LONG>(m_tInfo.fX + 32);
	m_tRectCollision[DIR::BOTTOM].top = SCAST<LONG>(m_tInfo.fY + 64);
	m_tRectCollision[DIR::BOTTOM].bottom = SCAST<LONG>(m_tInfo.fY + 128);
}

void CDesk::ChangeState()
{
	if (m_eCurDir != m_eDir)
	{
		m_eCurDir = m_eDir;
		switch (m_eDir)
		{
		case DIR::LEFT:
			m_pFrameKey = L"TableRight";
			break;
		case DIR::RIGHT:
			m_pFrameKey = L"TableLeft";
			break;
		case DIR::TOP:
			m_pFrameKey = L"TableDown";
			break;
		case DIR::BOTTOM:
			m_pFrameKey = L"TableUp";
			break;
		case DIR::END:
			m_pFrameKey = L"Table";
			break;
		default:
			break;
		}
	}
}

void CDesk::UpdateDrawRect()
{
	CObj::UpdateRect();
	if (m_bCheck)
	{
		switch (m_eCurDir)
		{
		case CDesk::LEFT:
		case CDesk::RIGHT:
			m_tCollisionRect.left = SCAST<LONG>(m_tInfo.fX - 25);
			m_tCollisionRect.right = SCAST<LONG>(m_tInfo.fX + 25);
			m_tCollisionRect.top = SCAST<LONG>(m_tRect.top);
			m_tCollisionRect.bottom = SCAST<LONG>(m_tRect.bottom);
			break;
		case CDesk::TOP:
		case CDesk::BOTTOM:
			m_tCollisionRect.left = SCAST<LONG>(m_tRect.left);
			m_tCollisionRect.right = SCAST<LONG>(m_tRect.right);
			m_tCollisionRect.top = SCAST<LONG>(m_tInfo.fY - 30);
			m_tCollisionRect.bottom = SCAST<LONG>(m_tInfo.fY + 30);
			break;
		default:
			break;
		}
	}
	else
	{
		m_tCollisionRect.left = SCAST<LONG>(m_tRect.left);
		m_tCollisionRect.right = SCAST<LONG>(m_tRect.right);
		m_tCollisionRect.top = SCAST<LONG>(m_tInfo.fY - 50);
		m_tCollisionRect.bottom = SCAST<LONG>(m_tInfo.fY + 50);
	}
}

void CDesk::Initialize()
{
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	m_bDead = false;
	m_eCurDir = DIR::END;
	m_eDir = DIR::END;
	m_pFrameKey = L"Table";
	m_iHp = 20;
	m_tInfo.iCX = 128;
	m_tInfo.iCY = 128;
	m_bCheck = false;
	m_tCollisionRect = {};
}

int CDesk::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_bRazerCool)
		if (m_dwRazer + 410 < GetTickCount())
			m_bRazerCool = false;

	UpdateDrawRect();

	RECT rc = {};
	bool bCheckCollision = false;
	for (int i = 0; i < DIR::END; ++i)
	{
		if (IntersectRect(&rc, m_pPlayer->Get_Rect(), &m_tRectCollision[i]) && !m_bCheck)
		{
			m_eDir = SCAST<DIR>(i);
			bCheckCollision = true;
			if (CKeyMgr::Get_Instance()->KeyDown('E'))
				m_bCheck = true;
		}
	}
	if (!bCheckCollision && !m_bCheck)
		m_eDir = DIR::END;

	return OBJ_NOEVENT;
}

void CDesk::LateUpdate()
{
	ChangeState();
}

void CDesk::Render(HDC hDC)
{
	CObj::UpdateRect();
	POS tPos = CScrollMgr::Get_MouseScroll();
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(m_pFrameKey);

	if(m_bCheck)
		GdiTransparentBlt(hDC, SCAST<int>(m_tRect.left + tPos.fX), SCAST<int>(m_tRect.top + tPos.fY), m_tInfo.iCX, m_tInfo.iCY, hMemDC, 0, m_tInfo.iCY, m_tInfo.iCX, m_tInfo.iCY, RGB(255, 0, 255));
	else
		GdiTransparentBlt(hDC, SCAST<int>(m_tRect.left + tPos.fX), SCAST<int>(m_tRect.top + tPos.fY), m_tInfo.iCX, m_tInfo.iCY, hMemDC, 0, 0, m_tInfo.iCX, m_tInfo.iCY, RGB(255, 0, 255));
}

void CDesk::Release()
{
}
