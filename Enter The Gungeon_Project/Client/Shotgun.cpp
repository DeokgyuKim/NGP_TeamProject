#include "stdafx.h"
#include "Shotgun.h"
#include "AngleBullet.h"

#include "AbstractFactory.h"
#include "ObjMgr.h"

CShotgun::CShotgun()
{
}


CShotgun::~CShotgun()
{
}

void CShotgun::CreateBullet()
{
	if (m_bReload == false && m_iBullet[BULLET::COUNT_NOW] > 0 && m_dwTime[GUN::RATEOFFIRE] + m_iTime[GUN::RATEOFFIRE] < GetTickCount())
	{
		CObj* pObj = NULL;
		for (int i = 0; i < 5; ++i)
		{

			pObj = (CAbstractFactory<CAngleBullet>::Create(m_tEdge.fX, m_tEdge.fY, m_fAngle - 10.f + 5 * i, 20.f, 14, 14));
			pObj->Set_Att(m_iAtt);
			if (m_pSubject == CObjMgr::Get_Instance()->Get_Player())
				CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::P_BULLET);
			else
				CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::M_BULLET);
		}
		CEffectMgr::MakeEffect(L"BulletOutEffect", FRAME{ 0, 7, 0, 1, 50, 0 }, m_tEdge.fX, m_tEdge.fY, 24, 24);
		CSoundMgr::Get_Instance()->PlaySound(L"Ak.wav", CSoundMgr::MAXCHANNEL);
		m_dwTime[GUN::RATEOFFIRE] = GetTickCount();
#ifdef _DEBUG
		//cout << m_iBullet[BULLET::COUNT_NOW] << " / " << m_iBullet[BULLET::COUNT_MAX] << endl;
#endif
		if (--m_iBullet[BULLET::COUNT_NOW] <= 0)
			Reload();
	}
}

