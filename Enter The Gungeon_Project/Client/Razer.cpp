#include "stdafx.h"
#include "Razer.h"
#include "Razerbullet.h"

#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "AngleBullet.h"
#include "COllisionMgr.h"


void CRazer::CreateBullet()
{
	if (m_bReload == false && m_iBullet[BULLET::COUNT_NOW] > 0 && m_dwTime[GUN::RATEOFFIRE] + m_iTime[GUN::RATEOFFIRE] < GetTickCount())
	{
		int iRand = rand() % m_iRebound - 5;
		float fMaxX = cosf(DEGREETORADIAN(m_fAngle) + DEGREETORADIAN(iRand)) * 1000.f;
		float fMaxY = sinf(DEGREETORADIAN(m_fAngle) + DEGREETORADIAN(iRand)) * 1000.f;
		float fPlusX = fMaxX / 100.f;
		float fPlusY = fMaxY / 100.f;

		for (int i = 0; i < 100; ++i)
		{
			CObj* pObj = (CAbstractFactory<CRazerbullet>::Create(m_tEdge.fX + fPlusX * i, m_tEdge.fY - fPlusY * i, 0, 20.f, 1, 1));
			//cout << m_tEdge.fX + i << endl;
			pObj->Set_Att(10);
			if (CCOllisionMgr::CheckRazerWall(pObj->Get_Info()))
				break;
			if (m_pSubject == CObjMgr::Get_Instance()->Get_Player())
				CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::RAZER);
		}
		m_dwTime[GUN::RATEOFFIRE] = GetTickCount();
		CSoundMgr::Get_Instance()->PlaySound(L"Ump.wav", CSoundMgr::MAXCHANNEL);
		CEffectMgr::MakeEffect(L"BulletOutEffect", FRAME{ 0, 7, 0, 1, 50, 0 }, m_tEdge.fX, m_tEdge.fY, 24, 24);
		if (--m_iBullet[BULLET::COUNT_NOW] <= 0)
			Reload();
	}
}

CRazer::CRazer()
{
}


CRazer::~CRazer()
{
}
