#include "stdafx.h"
#include "Chargegun.h"
#include "AngleBullet.h"

#include "KeyMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"

void CChargegun::CreateBullet()
{
	if (m_bReload == false && m_iBullet[BULLET::COUNT_NOW] > 0)
	{
		m_pBullet = CAbstractFactory<CAngleBullet>::Create(m_tEdge.fX, m_tEdge.fY, m_fAngle, 10.f, 14, 14);
		CAST<CAngleBullet*>(m_pBullet)->Set_Move(false);
		CAST<CAngleBullet*>(m_pBullet)->Set_Type(BULLET::CHARGE);
		m_pBullet->Set_Att(m_iAtt);
		CObjMgr::Get_Instance()->Push_Object(m_pBullet, OBJ::P_BULLET);
		CEffectMgr::MakeEffect(L"BulletOutEffect", FRAME{ 0, 7, 0, 1, 50, 0 }, m_tEdge.fX, m_tEdge.fY, 24, 24);
		CSoundMgr::Get_Instance()->PlaySound(L"ShotGun.mp3", CSoundMgr::MAXCHANNEL);
		if (--m_iBullet[BULLET::COUNT_NOW] <= 0)
			Reload();
	}
	
}

void CChargegun::KeyDown()
{
	if (m_bReload == false)
	{
		if (CKeyMgr::Get_Instance()->KeyPressing(VK_LBUTTON))
		{
			if (m_iCharge < 10)
				if (m_dwChargeTime + 100 < GetTickCount())
				{
					m_iCharge += 1;
					m_dwChargeTime = GetTickCount();
				}
		}
		if (CKeyMgr::Get_Instance()->KeyUp(VK_LBUTTON))
		{
			CreateBullet();
			m_pBullet->Set_Size(m_pBullet->Get_Info()->iCX + m_iCharge * 4, m_pBullet->Get_Info()->iCY + m_iCharge * 4);
			m_pBullet->Set_Att(m_pBullet->Get_Att() + m_iCharge * 4);
			m_pBullet->Set_Angle(m_fAngle);
			CAST<CAngleBullet*>(m_pBullet)->Set_Move(true);
			m_pBullet = NULL;
			cout << m_iCharge << endl;
			m_iCharge = 0;
		}
	}
	
}

CChargegun::CChargegun()
	: m_iCharge(1)
	, m_dwChargeTime(0)
{
}


CChargegun::~CChargegun()
{
}
