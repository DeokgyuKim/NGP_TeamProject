#include "stdafx.h"
#include "Gun.h"
#include "AngleBullet.h"

#include "ObjMgr.h"
#include "KeyMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"

#include "NetWork.h"

void CGun::Set_Edge(float fAngle)
{
	m_tEdge.fX = m_tInfo.fX + 40 * cosf(DEGREETORADIAN(fAngle));
	m_tEdge.fY = m_tInfo.fY - (40 * sinf(DEGREETORADIAN(fAngle)));
}

void CGun::Set_Target(bool bIsPlayer)
{
	if (bIsPlayer)
		m_pTarget = CObjMgr::Get_Instance()->Get_Mouse();
	else
		m_pTarget = CObjMgr::Get_Instance()->Get_Player();
}

void CGun::CreateBullet()
{
	if (m_bReload == false && m_iBullet[BULLET::COUNT_NOW] > 0 && m_dwTime[GUN::RATEOFFIRE] + m_iTime[GUN::RATEOFFIRE] < GetTickCount())
	{
		CNetwork::GetInstance()->SetInputKey(KEY_LBUTTON);
		int iRand = rand() % m_iRebound;
		CNetwork::GetInstance()->SetBulletInfo(m_tEdge.fX, m_tEdge.fY, m_fAngle + iRand);
		if(m_eGunType == GUN::NORMAL)
			CSoundMgr::Get_Instance()->PlaySound(L"Ump.wav", CSoundMgr::MAXCHANNEL);
		else if(m_eGunType == GUN::UMP)
			CSoundMgr::Get_Instance()->PlaySound(L"Ump.wav", CSoundMgr::MAXCHANNEL);
		else if(m_eGunType == GUN::AK)
			CSoundMgr::Get_Instance()->PlaySound(L"Ak.wav", CSoundMgr::MAXCHANNEL);
		/*
		CObj* pObj = (CAbstractFactory<CAngleBullet>::Create(m_tEdge.fX, m_tEdge.fY, m_fAngle + iRand, m_fSpeed, 14, 14));
		CEffectMgr::MakeEffect(L"BulletOutEffect", FRAME{ 0, 7, 0, 1, 50, 0 }, m_tEdge.fX, m_tEdge.fY, 24, 24);
		pObj->Set_Att(m_iAtt);
		if(m_pSubject == CObjMgr::Get_Instance()->Get_Player())
			CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::P_BULLET);
		else
			CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::M_BULLET);
		*/
		m_dwTime[GUN::RATEOFFIRE] = GetTickCount();
		if (--m_iBullet[BULLET::COUNT_NOW] <= 0)
			Reload();
#ifdef _DEBUG
		//cout << m_iBullet[BULLET::COUNT_NOW] << " / " << m_iBullet[BULLET::COUNT_MAX] << endl;
#endif
	}
}

void CGun::KeyDown()
{
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_LBUTTON))
	{
		CreateBullet();
	}
}

void CGun::Reload()
{
	if (m_iBullet[BULLET::COUNT_NOW] < m_iBullet[BULLET::COUNT_MAX] && (m_iBullet[BULLET::COUNT_ALL_NOW] > 0 || m_iBullet[BULLET::COUNT_ALL_MAX] == 0) && m_bReload == false)
	{
		m_bReload = true;
		m_dwTime[GUN::RELOAD] = GetTickCount();
		if(m_pSubject == CObjMgr::Get_Instance()->Get_Player())
			CSoundMgr::Get_Instance()->PlaySound(L"Reroad.mp3", CSoundMgr::MAXCHANNEL);
	}
}

CGun::CGun()
{
}


CGun::~CGun()
{
}

void CGun::Initialize()
{	
	m_tInfo.iCX = 20;
	m_tInfo.iCY = 20;
	m_fSpeed = 10.f;
	m_fAngle = 0.f;
	m_dwTime[GUN::END] = {};
	m_iTime[GUN::RATEOFFIRE] = 200;
	m_iTime[GUN::RELOAD] = 1000;
	m_iBullet[BULLET::COUNT_MAX] = 5;
	m_iBullet[BULLET::COUNT_NOW] = m_iBullet[BULLET::COUNT_MAX];
	m_bReload = false;
	m_bSelling = false;
	m_iRenderCount = 0;
}

int CGun::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	if (m_bSubject)
	{
		if (m_bReload)
		{
			m_fReloadTime = SCAST<float>(GetTickCount() - m_dwTime[GUN::RELOAD]) / SCAST<float>(m_iTime[GUN::RELOAD]);
			//if (m_dwTime[GUN::RELOAD] + m_iTime[GUN::RELOAD] < GetTickCount())
			if (GetTickCount() - m_dwTime[GUN::RELOAD] > SCAST<unsigned int>(m_iTime[GUN::RELOAD]))
			{
				m_bReload = false;
				if (m_iBullet[BULLET::COUNT_ALL_MAX] == 0)
				{
					m_iBullet[BULLET::COUNT_NOW] = m_iBullet[BULLET::COUNT_MAX];
				}
				else
				{
					int temp = m_iBullet[BULLET::COUNT_NOW];
					temp += m_iBullet[BULLET::COUNT_ALL_NOW];
					if (temp < m_iBullet[BULLET::COUNT_MAX])
					{
						m_iBullet[BULLET::COUNT_ALL_NOW] = 0;
						m_iBullet[BULLET::COUNT_NOW] = temp;
					}
					else
					{
						m_iBullet[BULLET::COUNT_ALL_NOW] = temp - m_iBullet[BULLET::COUNT_MAX];
						m_iBullet[BULLET::COUNT_NOW] = m_iBullet[BULLET::COUNT_MAX];
					}
				}
			}
		}
		//플레이어의 방향을 찾아 총의 좌표를 찾는다.
		if (m_pSubject->Get_Angle() < 90 || m_pSubject->Get_Angle() >= 270)			//플레이어가 오른쪽을 바라볼 때
		{
			m_tInfo.fX = m_pSubject->Get_Info()->fX + m_fDist;
			m_tInfo.fY = m_pSubject->Get_Info()->fY;
			switch (m_eGunType)
			{
			case GUN::NORMAL:
				m_pFrameKey = L"NormalRight";
				m_tInfo.iCX = 16;
				m_tInfo.iCY = 24;
				break;
			case GUN::AK:
				m_pFrameKey = L"AkRight";
				m_tInfo.iCX = 100;
				m_tInfo.iCY = 100;
				break;
			case GUN::UMP:
				m_pFrameKey = L"UmpRight";
				m_tInfo.iCX = 100;
				m_tInfo.iCY = 100;
				break;
			case GUN::SHOTGUN:
				m_pFrameKey = L"ShotgunRight";
				m_tInfo.iCX = 100;
				m_tInfo.iCY = 100;
				break;
			case GUN::RAZER:
				m_pFrameKey = L"RazerRight";
				m_tInfo.iCX = 100;
				m_tInfo.iCY = 100;
				break;
			case GUN::CHARGE:
				m_pFrameKey = L"ChargeRight";
				m_tInfo.iCX = 100;
				m_tInfo.iCY = 100;
				break;
			default:
				break;
			}
		}
		else if (m_pSubject->Get_Angle() >= 90 || m_pSubject->Get_Angle() < 270)		//플레이어가 왼쪽을 바라볼 때
		{
			m_tInfo.fX = m_pSubject->Get_Info()->fX - m_fDist;
			m_tInfo.fY = m_pSubject->Get_Info()->fY;
			switch (m_eGunType)
			{
			case GUN::NORMAL:
				m_pFrameKey = L"NormalLeft";
				m_tInfo.iCX = 16;
				m_tInfo.iCY = 24;
				break;
			case GUN::AK:
				m_pFrameKey = L"AkLeft";
				m_tInfo.iCX = 100;
				m_tInfo.iCY = 100;
				break;
			case GUN::UMP:
				m_pFrameKey = L"UmpLeft";
				m_tInfo.iCX = 100;
				m_tInfo.iCY = 100;
				break;
			case GUN::SHOTGUN:
				m_pFrameKey = L"ShotgunLeft";
				m_tInfo.iCX = 100;
				m_tInfo.iCY = 100;
				break;
			case GUN::RAZER:
				m_pFrameKey = L"RazerLeft";
				m_tInfo.iCX = 100;
				m_tInfo.iCY = 100;
				break;
			case GUN::CHARGE:
				m_pFrameKey = L"ChargeLeft";
				m_tInfo.iCX = 100;
				m_tInfo.iCY = 100;
				break;
			default:
				break;
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////

		//총과 마우스의 좌표 사이의 각을 찾아준다.

		//총과 플레이어 사이에 마우스 좌표가 있을 경우
		POS tTarget = { m_pTarget->Get_Info()->fX, m_pTarget->Get_Info()->fY };
		if (m_pSubject == CObjMgr::Get_Instance()->Get_Player())
		{
			tTarget.fX -= CScrollMgr::Get_Scroll().fX;
			tTarget.fY -= CScrollMgr::Get_Scroll().fY;
		}
		if (sqrtf((m_pSubject->Get_Info()->fX - tTarget.fX) * (m_pSubject->Get_Info()->fX - tTarget.fX) +
			(m_pSubject->Get_Info()->fY - tTarget.fY) * (m_pSubject->Get_Info()->fY - tTarget.fY)) <= m_fDist)
		{
			float fX = tTarget.fX - m_pSubject->Get_Info()->fX;
			float fY = tTarget.fY - m_pSubject->Get_Info()->fY;
			float fDist = sqrtf(fX * fX + fY * fY);

			float fAngle = acosf(fX / fDist);
			m_fAngle = RADIANTODEGREE(fAngle);
			if (m_tInfo.fY < tTarget.fY)
				m_fAngle = 360.f - m_fAngle;
		}
		else
		{
			float fX = tTarget.fX - m_tInfo.fX;
			float fY = tTarget.fY - m_tInfo.fY;
			float fDist = sqrtf(fX * fX + fY * fY);

			float fAngle = acosf(fX / fDist);
			m_fAngle = RADIANTODEGREE(fAngle);
			if (m_tInfo.fY < tTarget.fY)
				m_fAngle = 360.f - m_fAngle;
		}
		/////////////////////////////////////////////////////////////////////////////////////////

		if (m_pSubject->Get_Angle() < 90 || m_pSubject->Get_Angle() >= 270)
		{
			if (350 < m_fAngle || m_fAngle <= 10)
				m_iRenderCount = 0;
			else if (10 < m_fAngle && m_fAngle <= 30)
				m_iRenderCount = 1;
			else if (30 < m_fAngle && m_fAngle <= 50)
				m_iRenderCount = 2;
			else if (50 < m_fAngle && m_fAngle <= 70)
				m_iRenderCount = 3;
			else if (70 < m_fAngle && m_fAngle <= 90)
				m_iRenderCount = 4;
			else if (90 < m_fAngle && m_fAngle <= 110)
				m_iRenderCount = 5;
			else if (110 < m_fAngle && m_fAngle <= 180)
				m_iRenderCount = 6;
			else if (330 < m_fAngle && m_fAngle <= 350)
				m_iRenderCount = 7;
			else if (310 < m_fAngle && m_fAngle <= 330)
				m_iRenderCount = 8;
			else if (290 < m_fAngle && m_fAngle <= 310)
				m_iRenderCount = 9;
			else if (270 < m_fAngle && m_fAngle <= 290)
				m_iRenderCount = 10;
			else if (250 < m_fAngle && m_fAngle <= 270)
				m_iRenderCount = 11;
			else if (180 < m_fAngle && m_fAngle <= 250)
				m_iRenderCount = 12;
		}
		else
		{
			if (170 < m_fAngle && m_fAngle <= 190)
				m_iRenderCount = 0;
			else if (150 < m_fAngle && m_fAngle <= 170)
				m_iRenderCount = 1;
			else if (130 < m_fAngle && m_fAngle <= 150)
				m_iRenderCount = 2;
			else if (110 < m_fAngle && m_fAngle <= 130)
				m_iRenderCount = 3;
			else if (90 < m_fAngle && m_fAngle <= 110)
				m_iRenderCount = 4;
			else if (70 < m_fAngle && m_fAngle <= 90)
				m_iRenderCount = 5;
			else if (0 < m_fAngle && m_fAngle <= 70)
				m_iRenderCount = 6;
			else if (190 < m_fAngle && m_fAngle <= 210)
				m_iRenderCount = 7;
			else if (210 < m_fAngle && m_fAngle <= 230)
				m_iRenderCount = 8;
			else if (230 < m_fAngle && m_fAngle <= 250)
				m_iRenderCount = 9;
			else if (250 < m_fAngle && m_fAngle <= 270)
				m_iRenderCount = 10;
			else if (270 < m_fAngle && m_fAngle <= 290)
				m_iRenderCount = 11;
			else if (290 < m_fAngle && m_fAngle <= 360)
				m_iRenderCount = 12;
		}

		//총의 끝좌표를 찾는다.
		m_tEdge.fX = m_tInfo.fX + m_fDist * cosf(DEGREETORADIAN(m_fAngle));
		m_tEdge.fY = m_tInfo.fY - (m_fDist * sinf(DEGREETORADIAN(m_fAngle)));
		if(m_pSubject == CObjMgr::Get_Instance()->Get_Player())
			KeyDown();
	}


	return OBJ_NOEVENT;
}

void CGun::LateUpdate()
{
}

void CGun::Render(HDC hDC)
{
	//POS tPos[4] = {};
	//POS	tRotationPos[4] = {};
	//tPos[0] = { 0, - SCAST<float>(m_tInfo.iCY / 2) };
	//tPos[1] = { 0, SCAST<float>(m_tInfo.iCY / 2) };
	//tPos[2] = { SCAST<float>(m_tInfo.iCX), SCAST<float>(m_tInfo.iCY / 2) };
	//tPos[3] = { SCAST<float>(m_tInfo.iCX), -SCAST<float>(m_tInfo.iCY / 2) };
	//for (int i = 0; i < 4; ++i)
	//{
	//	tRotationPos[i].fX = m_tInfo.fX + tPos[i].fX * cosf(DEGREETORADIAN(m_fAngle)) - tPos[i].fY * sinf(DEGREETORADIAN(m_fAngle));
	//	tRotationPos[i].fY = m_tInfo.fY - (tPos[i].fX * sinf(DEGREETORADIAN(m_fAngle)) + tPos[i].fY * cosf(DEGREETORADIAN(m_fAngle)));
	//}
	//MoveToEx(hDC, SCAST<int>(tRotationPos[3].fX + tScorll.fX), SCAST<int>(tRotationPos[3].fY + tScorll.fY), nullptr);
	//for (int i = 0; i < 4; ++i)
	//	LineTo(hDC, SCAST<int>(tRotationPos[i].fX + tScorll.fX), SCAST<int>(tRotationPos[i].fY + tScorll.fY));
	//POINT pt[3] = {};
	//pt[0].x = SCAST<LONG>(tPos[0].fX);
	//pt[0].y = SCAST<LONG>(tPos[0].fY);

	//pt[0].x = SCAST<LONG>(tPos[3].fX);
	//pt[0].y = SCAST<LONG>(tPos[3].fY);

	//pt[0].x = SCAST<LONG>(tPos[1].fX);
	//pt[0].y = SCAST<LONG>(tPos[1].fY);
	CObj::UpdateRect();
	POS tScorll = CScrollMgr::Get_MouseScroll();
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(m_pFrameKey);

	BOOL b = GdiTransparentBlt(hDC, (int)(m_tRect.left + tScorll.fX), (int)(m_tRect.top + tScorll.fY), m_tInfo.iCX, m_tInfo.iCY,
		hMemDC, m_tInfo.iCX * m_iRenderCount, 0, m_tInfo.iCX, m_tInfo.iCY, RGB(255, 255, 255));

}

void CGun::Release()
{
}