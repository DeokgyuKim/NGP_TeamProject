#include "stdafx.h"
#include "ETGBoss.h"
#include "Boss.h"
#include "Desk.h"

#include "TileMgr.h"
#include "ObjMgr.h"
#include "UiMgr.h"
#include "AbstractFactory.h"

CETGBoss::CETGBoss()
{
}


CETGBoss::~CETGBoss()
{
	Release();
}

void CETGBoss::Initiailize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Monster/Boss/Boss_Wait.bmp", L"Boss_Wait");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Monster/Boss/Boss_Attack_Left.bmp", L"Boss_Attack_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Monster/Boss/Boss_Die.bmp", L"Boss_Die");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Monster/Boss/Boss_Attack_Right.bmp", L"Boss_Attack_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Monster/Boss/Boss_Ulti1_Standby.bmp", L"Boss_Ulti1_Standby");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Monster/Boss/Boss_Walk.bmp", L"Boss_Walk");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Monster/Boss/Boss_Die.bmp", L"Boss_Die");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Monster/Boss/BossIntro.bmp", L"BossIntro");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Monster/Boss/BossHPFrameUI.bmp", L"BossHPFrameUI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Monster/Boss/BossHPBar.bmp", L"BossHPBar");

	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(63.f * TILECX, 50.f * TILECY);
	CScrollMgr::Initialize(WINCX / 2 - 63.f * TILECX, WINCX / 2 - 50.f * TILECY);


	CObj* pObj = CAbstractFactory<CBoss>::Create(78.f * TILECX, 48.f * TILECY);
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::MONSTER);

	pObj = CAbstractFactory<CDesk>::Create(78.f * TILECX, 39.f * TILECY);
	CAST<CDesk*>(pObj)->UpdateCollisionRect();
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::DESK);

	pObj = CAbstractFactory<CDesk>::Create(78.f * TILECX, 57.f * TILECY);
	CAST<CDesk*>(pObj)->UpdateCollisionRect();
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::DESK);

	m_dwIntro = GetTickCount();
	m_bIntro = true;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iFrameVetical = 0;
	m_tFrame.iPlus = 1;
	m_tFrame.dwFrameSpeed = 150;
	m_tFrame.dwFrameTime = GetTickCount();
}

void CETGBoss::Update()
{
	if (m_bIntro && m_dwIntro + 3000 < GetTickCount())
		m_bIntro = false;
	if(!m_bIntro)
		CObjMgr::Get_Instance()->Update();
}

void CETGBoss::LateUpdate()
{
	if (!m_bIntro)
		CObjMgr::Get_Instance()->LateUpdate();
	else
	{
		if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
		{
			m_tFrame.iFrameStart += m_tFrame.iPlus;
			m_tFrame.dwFrameTime = GetTickCount();
		}
		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
		if (m_tFrame.iFrameStart < 0)
			m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
	}
	CSoundMgr::Get_Instance()->Update();
}

void CETGBoss::Render(HDC hDC)
{
	if (!m_bIntro)
	{
		CTileMgr::Get_Instance()->Render(hDC, false);
		CObjMgr::Get_Instance()->Render(hDC);
		CUiMgr::Get_Instance()->Render(hDC);
		CObjMgr::Get_Instance()->Get_Mouse()->Render(hDC);
	}
	else
	{
		HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"BossIntro");
		GdiTransparentBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 1280 * m_tFrame.iFrameStart, 0, 1280, 815, RGB(255, 0, 255));
	}
}

void CETGBoss::Release()
{
	//CObjMgr::Destroy_Instance();
	//CTileMgr::Destroy_Instance();
	//CUiMgr::Destroy_Instance();
}
