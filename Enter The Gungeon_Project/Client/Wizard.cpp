#include "stdafx.h"
#include "Wizard.h"
#include "WizardState.h"

#include "ObjMgr.h"
#include "AngleBullet.h"
#include "AbstractFactory.h"

CWizard::CWizard()
{
}


CWizard::~CWizard()
{
	Release();
}

void CWizard::CreateBullet(float fX, float fY)
{
	CObj* pObj = CAbstractFactory<CAngleBullet>::Create(fX, fY, m_fAngle, 10.f, 14, 14);
	pObj->Set_Att(m_iAtt);
	CAST<CAngleBullet*>(pObj)->Set_Move(false);
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::M_BULLET);
	m_lstBullet.push_back(pObj);
}

void CWizard::Initialize()
{
	m_eID = OBJ::WIZARD;
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	m_tInfo.iCX = 60;
	m_tInfo.iCY = 60;
	m_fDist = 80;
	m_fAngle = 0.f;
	m_iAtt = 1;
	m_iHp = 120;
	m_fSpeed = 2.f;
	m_pState = new StateMachine<CWizard>(this);
	m_pState->SetCurrentState(CWizardState_IDLE::Instance());
	m_bRazerCool = false;
	m_dwRazer = 0;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Monster/GhostMonster.bmp", L"GhostMonster");
	Set_Frame(0, 5, 0, 200);
	Set_FrameKey(L"GhostMonster");
	Set_Frame_Plus(true);
}

int CWizard::Update()
{
	if (m_bDead)
	{
		if (!m_lstBullet.empty())
		{
			for (auto& iter = m_lstBullet.begin(); iter != m_lstBullet.end(); ++iter)
			{
				auto& finditer = find(CObjMgr::Get_Instance()->Get_M_LstBullet()->begin(), CObjMgr::Get_Instance()->Get_M_LstBullet()->end(), *iter);
				if (finditer != CObjMgr::Get_Instance()->Get_M_LstBullet()->end())
				{
					delete *finditer;
					CObjMgr::Get_Instance()->Get_M_LstBullet()->erase(finditer);
				}
			}
			m_lstBullet.clear();
		}
		return OBJ_DEAD;
	}
	if (m_bRazerCool)
		if (m_dwRazer + 100 < GetTickCount())
			m_bRazerCool = false;
	//if (m_pPlayer->Get_Info()->fX > m_tInfo.fX)
	//{
	//	//¿À¸¥ÂÊ
	//	if (m_eDir != MONSTER::RIGHT)
	//	{
	//		Set_Frame(0, 5, 0, 200);
	//		m_eDir = MONSTER::RIGHT;
	//	}
	//}
	//else
	//{
	//	//¿ÞÂÊ
	//	if (m_eDir != MONSTER::LEFT)
	//	{
	//		Set_Frame(0, 5, 0, 200);
	//		m_eDir = MONSTER::LEFT;
	//	}
	//}

	m_pState->Update();



	return OBJ_NOEVENT;
}

void CWizard::LateUpdate()
{
}

void CWizard::Render(HDC hDC)
{
	CObj::UpdateRect();
	POS tPos = CScrollMgr::Get_MouseScroll();
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(m_pFrameKey);
	GdiTransparentBlt(hDC, SCAST<int>(m_tRect.left + tPos.fX), SCAST<int>(m_tRect.top + tPos.fY), m_tInfo.iCX, m_tInfo.iCY, hMemDC, m_tInfo.iCX * m_tFrame.iFrameStart, m_tInfo.iCY * m_tFrame.iFrameVetical, m_tInfo.iCX, m_tInfo.iCY, RGB(255, 0, 255));
}

void CWizard::Release()
{
	CEffectMgr::MakeEffect(L"MonsterDie", FRAME(0, 7, 0, 1, 50, 0), m_tInfo.fX, m_tInfo.fY, 64, 64, 1);
	m_pPlayer->Set_Gold(m_pPlayer->Get_Gold() + 1);
}
