#include "stdafx.h"
#include "OtherPlayer.h"
#include "Gun.h"
#include "Shotgun.h"
#include "Chargegun.h"
#include "Razer.h"
#include "PlayerState.h"
#include "Dreadshot.h"

#include "ObjMgr.h"
#include "KeyMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"


COtherPlayer::COtherPlayer()
{
}


COtherPlayer::~COtherPlayer()
{
	Release(); 
}

void COtherPlayer::Initialize()
{
	m_tInfo.fX = 1000;
	m_tInfo.fY = 800;
	CScrollMgr::Initialize(WINCX / 2 - m_tInfo.fX, WINCY / 2 - m_tInfo.fY);
	m_tInfo.iCX = 60;
	m_tInfo.iCY = 60;
	m_fSpeed = 4.f;
	m_fRollAngle = 0.f;
	m_iDreadshot = 2;
	m_bRoll = false;
	m_bDamaged = false;
	m_pMouse = CObjMgr::Get_Instance()->Get_Mouse();
	m_vecGun.reserve(10);
	m_iGunCount = 0;
	m_iHp = 6;
	m_iGold = 10;
	m_iGunNow = 0;
	m_eID = OBJ::ME;
	CObj* pObj = NULL;
	pObj = CAbstractFactory<CGun>::CreateGun(this, 25.f, 1, true);
	pObj->Set_Size(14, 14);
	//pObj->Set_ID(OBJ::NORMAL);
	pObj->Set_Att(10);
	CAST<CGun*>(pObj)->Set_GunType(GUN::NORMAL);
	CAST<CGun*>(pObj)->Set_Speed(10.f);
	CAST<CGun*>(pObj)->Set_BulletState(5, 0);
	CAST<CGun*>(pObj)->Set_Time(1000, 200);
	m_vecGun.emplace_back(pObj);
	++m_iGunCount;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Gun/NormalBulletUI.bmp", L"NormalBulletUI");

	Set_Frame(0, 3, 0, 100);
	Set_Frame_Plus(true);
	Set_FrameKey(L"Player_Down");
	m_bCheat = false;
}

int COtherPlayer::Update()
{
	//cout << m_iGold << endl;
	if (m_bDead && !m_bCheat)
		return OBJ_PLAYERDEAD;


	return OBJ_NOEVENT;
}

void COtherPlayer::LateUpdate()
{
}

void COtherPlayer::Render(HDC hDC)
{
	CObj::UpdateRect();
	m_vecGun[m_iGunNow]->Render(hDC);


	
	POS tPos = CScrollMgr::Get_MouseScroll();
	//MoveToEx(hDC, SCAST<int>(m_tInfo.fX + tPos.fX), SCAST<int>(m_tInfo.fY + tPos.fY), nullptr);
	//LineTo(hDC, SCAST<int>(m_tInfo.fX + cosf(DEGREETORADIAN(m_fAngle)) * 10.f + tPos.fX), SCAST<int>(m_tInfo.fY - sinf(DEGREETORADIAN(m_fAngle)) * 10.f + tPos.fY));
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(m_pFrameKey);
	GdiTransparentBlt(hDC, SCAST<int>(m_tRect.left + tPos.fX), SCAST<int>(m_tRect.top + tPos.fY), m_tInfo.iCX, m_tInfo.iCY, hMemDC, m_tInfo.iCX * m_tFrame.iFrameStart, m_tInfo.iCY * m_tFrame.iFrameVetical, m_tInfo.iCX, m_tInfo.iCY, RGB(255, 0, 255));
	//Rectangle(hDC, SCAST<int>(m_tRect.left), SCAST<int>(m_tRect.top), SCAST<int>(m_tRect.right), SCAST<int>(m_tRect.bottom));
}

void COtherPlayer::Release()
{
	for (auto& pElement : m_vecGun)
	{
		pElement->Release();
		delete pElement;
	}
}