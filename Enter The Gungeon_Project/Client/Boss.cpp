#include "stdafx.h"
#include "Boss.h"
#include "BossState.h"

#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "AngleBullet.h"
#include "Radialbullet.h"

void CBoss::Set_Dead()
{
	if (m_bDead)
		return;
	m_pState->ChangeState(CBossState_IDLE::Instance());
	m_bDead = true;
	Set_FrameKey(L"Boss_Die");
	Set_Size(88, 164);
	Set_Frame(0, 10, 0, 300);
	m_dwDead = GetTickCount();
}

void CBoss::CreateAtt(float fX, float fY, float fAngle)
{
	CObj* pObj = CAbstractFactory<CAngleBullet>::Create(fX, fY, fAngle, 5.f, 14, 14);
	CAST<CAngleBullet*>(pObj)->Set_Type(BULLET::NORMAL);
	pObj->Set_Att(m_iAtt);
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::M_BULLET);
}

void CBoss::CreateRadial(float fAngle)
{
	CObj* pObj = CAbstractFactory<CRadialbullet>::Create(m_tInfo.fX, m_tInfo.fY, fAngle);
	//CAST<CRadialbullet*>(pObj)->Set_Type(BULLET::NORMAL);
	pObj->Set_Att(m_iAtt);
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::M_BULLET);
}

CBoss::CBoss()
{
}


CBoss::~CBoss()
{
}

void CBoss::Initialize()
{
	m_eID = OBJ::BOSS;
	m_tInfo.fX = 1000.f;
	m_tInfo.fY = 1000.f;
	m_tInfo.iCX = 78;
	m_tInfo.iCY = 140;
	m_fSpeed = 2.f;
	m_iHp = 497;
	m_iAtt = 1;
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	m_pState = new StateMachine<CBoss>(this);
	m_pState->SetCurrentState(CBossState_IDLE::Instance());
	m_bRazerCool = false;
	m_dwRazer = 0;
	Set_Frame(0, 5, 0, 300);
	Set_FrameKey(L"Boss_Wait");
	Set_Frame_Plus(true);
}

int CBoss::Update()
{
	if (m_bDead)
	{
		if (m_dwDead + 3000 < GetTickCount())
		{
			return OBJ_BOSSDEAD;
		}
	}
	m_pState->Update();
	if (m_bRazerCool)
		if (m_dwRazer + 100 < GetTickCount())
			m_bRazerCool = false;
	return OBJ_NOEVENT;
}

void CBoss::LateUpdate()
{
	m_tCollisionRect.left =		(LONG)(m_tInfo.fX - 35.f);
	m_tCollisionRect.right =	(LONG)(m_tInfo.fX + 35.f);
	m_tCollisionRect.top =		(LONG)(m_tInfo.fY - 60.f);
	m_tCollisionRect.bottom =	(LONG)(m_tInfo.fY + 70.f);
}

void CBoss::Render(HDC hDC)
{
	CObj::UpdateRect();
	POS tPos = CScrollMgr::Get_MouseScroll();
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(m_pFrameKey);
	BOOL b = GdiTransparentBlt(hDC, SCAST<int>(m_tRect.left + tPos.fX), SCAST<int>(m_tRect.top + tPos.fY), m_tInfo.iCX, m_tInfo.iCY, hMemDC, m_tInfo.iCX * m_tFrame.iFrameStart, m_tInfo.iCY * m_tFrame.iFrameVetical, m_tInfo.iCX, m_tInfo.iCY, RGB(255, 0, 255));
}

void CBoss::Release()
{
}
