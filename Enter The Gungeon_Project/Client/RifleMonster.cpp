#include "stdafx.h"
#include "RifleMonster.h"
#include "Gun.h"
#include "RifleMonsterState.h"

#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"

CRifleMonster::CRifleMonster()
{
}


CRifleMonster::~CRifleMonster()
{
	Release();
}

void CRifleMonster::Initialize()
{
	m_eID = OBJ::RIFLE;
	m_tInfo.fX = 900.f;
	m_tInfo.fY = 350.f;
	m_tInfo.iCX = 60;
	m_tInfo.iCY = 60;
	m_fSpeed = 2.f;
	m_iHp = 70;
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();

	m_pGun = CAbstractFactory<CGun>::CreateGun(this, 20.f, 1, false);
	m_pGun->Set_Size(14, 14);
	m_pGun->Set_Att(1);
	CAST<CGun*>(m_pGun)->Set_GunType(GUN::AK);
	CAST<CGun*>(m_pGun)->Set_Speed(5.f);
	CAST<CGun*>(m_pGun)->Set_BulletState(20, 0);
	CAST<CGun*>(m_pGun)->Set_Time(1000, 50);

	m_pState = new StateMachine<CRifleMonster>(this);
	m_pState->SetCurrentState(CRifleMonsterState_IDLE::Instance());
	m_bRazerCool = false;
	m_dwRazer = 0;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Monster/BlueMonster.bmp", L"BlueMonster");
	Set_Frame(0, 5, 0, 200);
	Set_FrameKey(L"BlueMonster");
	Set_Frame_Plus(true);
}

int CRifleMonster::Update()
{
	if (m_bDead || m_iHp <= 0)
		return OBJ_DEAD;
	if (m_bRazerCool)
		if (m_dwRazer + 100 < GetTickCount())
			m_bRazerCool = false;
	m_pState->Update();

	//if (m_bShot)
	//{
	//	if (CAST<CGun*>(m_pGun)->Get_BulletState()[BULLET::COUNT_NOW] <= 0)
	//	{
	//		CAST<CGun*>(m_pGun)->Reload();
	//		m_bShot = false;
	//	}
	//	else
	//	{
	//		m_fAngle = m_fAngle + (60.f / 65.f);
	//		m_pGun->Set_Angle(m_fAngle);
	//		CAST<CGun*>(m_pGun)->CreateBullet();
	//	}
	//}
	//else
	//{
	//	float fX = m_pPlayer->Get_Info()->fX - m_tInfo.fX;
	//	float fY = m_pPlayer->Get_Info()->fY - m_tInfo.fY;
	//	float fDist = sqrtf(fX * fX + fY * fY);

	//	float fAngle = acosf(fX / fDist);
	//	m_fAngle = RADIANTODEGREE(fAngle);
	//	if (m_tInfo.fY < m_pPlayer->Get_Info()->fY)
	//		m_fAngle = 360.f - m_fAngle;
	//	m_pGun->Update();
	//	//플레이어가 일정 거리 내에 들어오면 총을 쏜다.
	//	if (fDist < 200)
	//	{
	//		float fX = m_pPlayer->Get_Info()->fX - m_pGun->Get_Info()->fX;
	//		float fY = m_pPlayer->Get_Info()->fY - m_pGun->Get_Info()->fY;
	//		float fDist = sqrtf(fX * fX + fY * fY);

	//		float fAngle = acosf(fX / fDist);
	//		m_fAngle = RADIANTODEGREE(fAngle);
	//		if (m_pGun->Get_Info()->fY < m_pPlayer->Get_Info()->fY)
	//			m_fAngle = 360.f - m_fAngle;
	//		m_fAngle -= 30.f;
	//		m_bShot = true;
	//	}
	//	//플레이어가 일정 거리 내에 들어오면 따라간다.
	//	else if (fDist < 400)
	//	{
	//		m_tInfo.fX += cosf(DEGREETORADIAN(m_fAngle)) * m_fSpeed;
	//		m_tInfo.fY -= sinf(DEGREETORADIAN(m_fAngle)) * m_fSpeed;
	//	}
	//	//플레이어가 거리 내에 들어오지 않았을 경우
	//	else
	//	{
	//		CAST<CGun*>(m_pGun)->Reload();
	//	}
	//}
	return OBJ_NOEVENT;
}

void CRifleMonster::LateUpdate()
{
	m_pGun->LateUpdate();
}

void CRifleMonster::Render(HDC hDC)
{
	m_pGun->Render(hDC);
	CObj::UpdateRect();
	POS tPos = CScrollMgr::Get_MouseScroll();
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(m_pFrameKey);
	GdiTransparentBlt(hDC, SCAST<int>(m_tRect.left + tPos.fX), SCAST<int>(m_tRect.top + tPos.fY), m_tInfo.iCX, m_tInfo.iCY, hMemDC, m_tInfo.iCX * m_tFrame.iFrameStart, m_tInfo.iCY * m_tFrame.iFrameVetical, m_tInfo.iCX, m_tInfo.iCY, RGB(255, 0, 255));

	//Rectangle(hDC, SCAST<int>(m_tRect.left + tPos.fX), SCAST<int>(m_tRect.top + tPos.fY), SCAST<int>(m_tRect.right + tPos.fX), SCAST<int>(m_tRect.bottom + tPos.fY));
}

void CRifleMonster::Release()
{
	m_pGun->Release();
	CEffectMgr::MakeEffect(L"MonsterDie", FRAME(0, 7, 0, 1, 50, 0), m_tInfo.fX, m_tInfo.fY, 64, 64, 1);
	m_pPlayer->Set_Gold(m_pPlayer->Get_Gold() + 1);
}
