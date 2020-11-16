#include "stdafx.h"
#include "Monster.h"
#include "Gun.h"
#include "MonsterState.h"

#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"

CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	m_eID = OBJ::NORMAL;
	m_tInfo.fX = 700.f; 
	m_tInfo.fY = 350.f;
	m_tInfo.iCX = 60; 
	m_tInfo.iCY = 60; 
	m_fSpeed = 2.f; 
	m_iHp = 50;
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	m_pGun = CAbstractFactory<CGun>::CreateGun(this, 20.f, 1, false);
	m_pGun->Set_Att(1);
	m_pGun->Set_Speed(5.f);
	m_pGun->Set_Size(14, 14);
	CAST<CGun*>(m_pGun)->Set_BulletState(1, 0);
	CAST<CGun*>(m_pGun)->Set_Time(0, 1000);
	m_pState = new StateMachine<CMonster>(this);
	m_pState->SetCurrentState(CMonsterState_IDLE::Instance());
	m_bRazerCool = false;
	m_dwRazer = 0;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Monster/RedMonster.bmp", L"RedMonster");
	Set_Frame(0, 5, 0, 200);
	Set_FrameKey(L"RedMonster");
	Set_Frame_Plus(true);
	m_eDir = MONSTER::RIGHT;
}

int CMonster::Update()
{
	if (m_bDead || m_iHp <= 0)
		return OBJ_DEAD;
	if (m_bRazerCool)
		if (m_dwRazer + 100 < GetTickCount())
			m_bRazerCool = false;

	float fX = m_pPlayer->Get_Info()->fX - m_tInfo.fX;
	float fY = m_pPlayer->Get_Info()->fY - m_tInfo.fY;
	float fDist = sqrtf(fX * fX + fY * fY);

	float fAngle = acosf(fX / fDist);
	m_fAngle = RADIANTODEGREE(fAngle);
	if (m_tInfo.fY < m_pPlayer->Get_Info()->fY)
		m_fAngle = 360.f - m_fAngle;
	if (45 < m_fAngle && m_fAngle <= 135)
	{
		if (m_eDir != MONSTER::UP)
		{
			Set_Frame(0, 5, 1, 200);
			m_eDir = MONSTER::UP;
		}
	}
	else if (135 < m_fAngle && m_fAngle <= 225)
	{
		if (m_eDir != MONSTER::LEFT)
		{
			Set_Frame(0, 5, 2, 200);
			m_eDir = MONSTER::LEFT;
		}
	}
	else if (225 < m_fAngle && m_fAngle <= 315)
	{
		if (m_eDir != MONSTER::DOWN)
		{
			Set_Frame(0, 5, 3, 200);
			m_eDir = MONSTER::DOWN;
		}
	}
	else
	{
		if (m_eDir != MONSTER::RIGHT)
		{
			Set_Frame(0, 5, 0, 200);
			m_eDir = MONSTER::RIGHT;
		}
	}
	m_pGun->Update();
	m_pState->Update();
	////플레이어가 일정 거리 내에 들어오면 총을 쏜다.
	//if (fDist < 200)
	//{
	//	CAST<CGun*>(m_pGun)->CreateBullet();
	//}
	////플레이어가 일정 거리 내에 들어오면 따라간다.
	//else if (fDist < 400)
	//{
	//	m_tInfo.fX += cosf(DEGREETORADIAN(m_fAngle)) * m_fSpeed;
	//	m_tInfo.fY -= sinf(DEGREETORADIAN(m_fAngle)) * m_fSpeed;
	//}
	////플레이어가 거리 내에 들어오지 않았을 경우
	//else
	//{

	//}
	return OBJ_NOEVENT;
}

void CMonster::LateUpdate()
{
	m_pGun->LateUpdate();
}

void CMonster::Render(HDC hDC)
{
	m_pGun->Render(hDC);
	CObj::UpdateRect(); 
	POS tPos = CScrollMgr::Get_MouseScroll();
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(m_pFrameKey);
	GdiTransparentBlt(hDC, SCAST<int>(m_tRect.left + tPos.fX), SCAST<int>(m_tRect.top + tPos.fY), m_tInfo.iCX, m_tInfo.iCY, hMemDC, m_tInfo.iCX * m_tFrame.iFrameStart, m_tInfo.iCY * m_tFrame.iFrameVetical, m_tInfo.iCX, m_tInfo.iCY, RGB(255, 0, 255));

}

void CMonster::Release()
{
	CEffectMgr::MakeEffect(L"MonsterDie", FRAME(0, 7, 0, 1, 50, 0), m_tInfo.fX, m_tInfo.fY, 64, 64, 1);
	m_pGun->Release();
	m_pPlayer->Set_Gold(m_pPlayer->Get_Gold() + 1);
}
