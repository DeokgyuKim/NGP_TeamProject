#include "stdafx.h"
#include "Bird.h"
#include "BirdState.h"
#include "Radialbullet.h"
#include "Boom.h"

#include "ObjMgr.h"
#include "AbstractFactory.h"

CBird::CBird()
{
}


CBird::~CBird()
{
	Release();
}

void CBird::CreateBullet()
{
	//보스패턴
	//CObj* pObj = CAbstractFactory<CRadialbullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle);
	//pObj->Set_Att(m_iAtt);
	//CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::M_BULLET);
	CObj* pObj = CAbstractFactory<CBoom>::Create(m_tInfo.fX, m_tInfo.fY);
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::BOOM);
}

void CBird::Initialize()
{
	m_eID = OBJ::BIRD;
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	m_tInfo.iCX = 60;
	m_tInfo.iCY = 60;
	m_fDist = 80;
	m_fAngle = 0.f;
	m_iAtt = 1;
	m_iHp = 120;
	m_fSpeed = 2.f;
	m_pState = new StateMachine<CBird>(this);
	m_pState->SetCurrentState(CBirdState_IDLE::Instance());
	m_bRazerCool = false;
	m_dwRazer = 0;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Monster/BirdMonsterLeft.bmp", L"BirdMonsterLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Monster/BirdMonsterRight.bmp", L"BirdMonsterRight");
	Set_Frame(0, 3, 0, 200);
	Set_FrameKey(L"BirdMonsterLeft");
	Set_Frame_Plus(true);
}

int CBird::Update()
{
	if (m_bDead)
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
	if (m_pPlayer->Get_Info()->fX > m_tInfo.fX)
	{
		Set_FrameKey(L"BirdMonsterRight");
	}
	else
	{
		Set_FrameKey(L"BirdMonsterLeft");
	}

	m_pState->Update();



	return OBJ_NOEVENT;
}

void CBird::LateUpdate()
{
}

void CBird::Render(HDC hDC)
{
	CObj::UpdateRect();
	POS tPos = CScrollMgr::Get_MouseScroll();
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(m_pFrameKey);
	GdiTransparentBlt(hDC, SCAST<int>(m_tRect.left + tPos.fX), SCAST<int>(m_tRect.top + tPos.fY), m_tInfo.iCX, m_tInfo.iCY, hMemDC, m_tInfo.iCX * m_tFrame.iFrameStart, m_tInfo.iCY * m_tFrame.iFrameVetical, m_tInfo.iCX, m_tInfo.iCY, RGB(255, 0, 255));
}

void CBird::Release()
{
	CEffectMgr::MakeEffect(L"MonsterDie", FRAME(0, 7, 0, 1, 50, 0), m_tInfo.fX, m_tInfo.fY, 64, 64, 1);
	m_pPlayer->Set_Gold(m_pPlayer->Get_Gold() + 1);
}
