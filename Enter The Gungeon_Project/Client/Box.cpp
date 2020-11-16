#include "stdafx.h"
#include "Box.h"
#include "Shotgun.h"

#include "SceneMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"

CBox::CBox()
{
}


CBox::~CBox()
{
	Release();
}

void CBox::Initialize()
{
	m_eID = OBJ::BOXOBJ;
	m_tInfo.iCX = 80;
	m_tInfo.iCY = 60;
	m_bDead = false;
	m_iHp = 60;
	m_pFrameKey = L"ItemBox1";
}

int CBox::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_iCount = m_iHp / 10;
	if (m_iCount < 0)
		m_iCount = 0;
	if (m_iCount > 5)
		m_iCount = 5;

	return OBJ_NOEVENT;
}

void CBox::LateUpdate()
{
}

void CBox::Render(HDC hDC)
{
	CObj::UpdateRect();
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(m_pFrameKey);
	POS tPos = CScrollMgr::Get_MouseScroll();
	GdiTransparentBlt(hDC, (int)(m_tRect.left + tPos.fX), (int)(m_tRect.top + tPos.fY), 
		m_tInfo.iCX, m_tInfo.iCY, hMemDC, m_tInfo.iCX * m_iCount, 0, m_tInfo.iCX, m_tInfo.iCY, RGB(255, 0, 255));
	//Rectangle(hDC, m_tRect.left + tPos.fX, m_tRect.top + tPos.fY, m_tRect.right + tPos.fX, m_tRect.bottom + tPos.fY);
}

void CBox::Release()
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() != CSceneMgr::SCENE_STAGE)
		return;
	CObj* pObj = NULL;

	switch (m_eType)
	{
	case GUN::NORMAL:
		break;
	case GUN::AK:
		pObj = CAbstractFactory<CGun>::CreateGun(nullptr, 20.f, 5, true);
		pObj->Set_FrameKey(L"AkRight");
		pObj->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		pObj->Set_Angle(0.f);
		pObj->Set_Size(100, 100);
		//pObj->Set_ID(OBJ::NORMAL);
		pObj->Set_Att(8);
		CAST<CGun*>(pObj)->Set_GunType(GUN::AK);
		CAST<CGun*>(pObj)->Set_Speed(20.f);
		CAST<CGun*>(pObj)->Set_BulletState(30, 300);
		CAST<CGun*>(pObj)->Set_Time(1000, 50);
		CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::GUN);
		break;
	case GUN::UMP:
		pObj = CAbstractFactory<CGun>::CreateGun(nullptr, 30.f, 15, true);
		pObj->Set_FrameKey(L"UmpRight");
		pObj->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		pObj->Set_Angle(0.f);
		pObj->Set_Size(100, 100);
		//pObj->Set_ID(OBJ::NORMAL);
		pObj->Set_Att(5);
		CAST<CGun*>(pObj)->Set_GunType(GUN::UMP);
		CAST<CGun*>(pObj)->Set_Speed(20.f);
		CAST<CGun*>(pObj)->Set_BulletState(20, 400);
		CAST<CGun*>(pObj)->Set_Time(1000, 20);
		CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::GUN);
		break;
	case GUN::SHOTGUN:
		pObj = CAbstractFactory<CShotgun>::CreateGun(nullptr, 20.f, 0, true);
		pObj->Set_FrameKey(L"ShotgunRight");
		pObj->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		pObj->Set_Angle(0.f);
		pObj->Set_Size(100, 100);
		//pObj->Set_ID(OBJ::SHOTGUN);
		pObj->Set_Att(5);
		CAST<CGun*>(pObj)->Set_GunType(GUN::SHOTGUN);
		CAST<CGun*>(pObj)->Set_Speed(10.f);
		CAST<CGun*>(pObj)->Set_BulletState(3, 100);
		CAST<CGun*>(pObj)->Set_Time(1000, 400);
		CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::GUN);
		break;
	case GUN::RAZER:
		break;
	case GUN::CHARGE:
		break;
	default:
		break;
	}
	CSoundMgr::Get_Instance()->PlaySound(L"ItemBoxOpen.mp3", CSoundMgr::MAXCHANNEL);
}
