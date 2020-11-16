#include "stdafx.h"
#include "Shop.h"
#include "Chargegun.h"
#include "Razer.h"

#include "AbstractFactory.h"
#include "COllisionMgr.h"
#include "ObjMgr.h"


CShop::CShop()
{
}


CShop::~CShop()
{
}

void CShop::Initialize()
{
	m_tInfo.fX = 1305;
	m_tInfo.fY = 2300;
	m_tInfo.iCX = 733;
	m_tInfo.iCY = 422;
	m_bDead = false;
	m_pFrameKey = L"Shop";
	Set_Frame(0, 1, 0, 250);
	Set_Frame_Plus(true);
	CObj::UpdateRect();
	m_tCollisionRect[0].left = m_tRect.left + 96;
	m_tCollisionRect[0].top = m_tRect.bottom;
	m_tCollisionRect[0].right = m_tRect.left + 318;
	m_tCollisionRect[0].bottom = m_tRect.bottom + 64;

	m_tCollisionRect[1].left = m_tRect.left + 424;
	m_tCollisionRect[1].top = m_tRect.bottom;
	m_tCollisionRect[1].right = m_tRect.left + 646;
	m_tCollisionRect[1].bottom = m_tRect.bottom + 64;

	m_tCollisionRect[2].left = m_tRect.right;
	m_tCollisionRect[2].top = m_tRect.top + 64;
	m_tCollisionRect[2].right = m_tRect.right + 64;
	m_tCollisionRect[2].bottom = m_tRect.top + 154;

	m_tCollisionRect[3].left = m_tRect.right;
	m_tCollisionRect[3].top = m_tRect.top + 174;
	m_tCollisionRect[3].right = m_tRect.right + 64;
	m_tCollisionRect[3].bottom = m_tRect.top + 264;
	m_iValue = 1;
	m_dwValue = 0;
	m_bValue = false;

	m_iSell[0] = 2;
	m_iSell[1] = 2;
	m_iSell[2] = 5;
	m_iSell[3] = 10;

	CObj* pObj = CAbstractFactory<CChargegun>::CreateGun(nullptr, 40.f, 0, true);
	pObj->Set_FrameKey(L"ChargeRight");
	pObj->Set_Angle(0.f);
	pObj->Set_Size(100, 100);
	pObj->Set_Pos(1600, 2190);
	//pObj->Set_ID(OBJ::CHARGE);
	pObj->Set_Att(5);
	CAST<CGun*>(pObj)->Set_GunType(GUN::CHARGE);
	CAST<CGun*>(pObj)->Set_Speed(10.f);
	CAST<CGun*>(pObj)->Set_BulletState(1, 100);
	CAST<CGun*>(pObj)->Set_Time(1000, 0);
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::GUN);

	pObj = CAbstractFactory<CRazer>::CreateGun(nullptr, 40.f, 10, true);
	pObj->Set_FrameKey(L"RazerRight");
	pObj->Set_Angle(0.f);
	pObj->Set_Size(100, 100);
	pObj->Set_Pos(1600, 2280);
	//pObj->Set_ID(OBJ::CHARGE);
	pObj->Set_Att(1);
	CAST<CGun*>(pObj)->Set_GunType(GUN::RAZER);
	CAST<CGun*>(pObj)->Set_Speed(10.f);
	CAST<CGun*>(pObj)->Set_BulletState(5, 100);
	CAST<CGun*>(pObj)->Set_Time(1000, 800);
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::GUN);

}

int CShop::Update()
{
	RECT rt = { 960, 2100, 1980, 2900 };
	if (!m_bValue)
	{
		if (CCOllisionMgr::Collision_Shop_Bullet(&rt, CObjMgr::Get_Instance()->Get_P_LstBullet(), 
			CObjMgr::Get_Instance()->Get_Razer()))
		{
			m_iValue *= 2;
			m_bValue = true;
			m_dwValue = GetTickCount();
		}
	}
	else
	{
		if (m_dwValue + 2000 < GetTickCount())
		{
			m_bValue = false;
		}
	}
	return 0;
}

void CShop::LateUpdate()
{
	FrameMove();
}

void CShop::Render(HDC hDC)
{
	CObj::UpdateRect();
	POS tPos = CScrollMgr::Get_MouseScroll();
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(m_pFrameKey);
	GdiTransparentBlt(hDC, (int)(m_tRect.left + tPos.fX), (int)(m_tRect.top + tPos.fY), m_tInfo.iCX, m_tInfo.iCY,
		hMemDC, m_tInfo.iCX * m_tFrame.iFrameStart, 0, m_tInfo.iCX, m_tInfo.iCY, RGB(255, 255, 255));

#ifdef _DEBUG
	for (int i = 0; i < 4; ++i)
	{
		Rectangle(hDC, (int)(m_tCollisionRect[i].left + tPos.fX), (int)(m_tCollisionRect[i].top + tPos.fY),
			(int)(m_tCollisionRect[i].right + tPos.fX), (int)(m_tCollisionRect[i].bottom + tPos.fY));
	}
#endif

	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(0, 0, 0));
	HFONT hFont = CreateFont(30, 0, 0, 0, FW_NORMAL, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("µÕ±Ù¸ð²Ã"));
	HFONT oldFont = (HFONT)SelectObject(hDC, hFont);
	TCHAR tValue[32] = L"";
	swprintf_s(tValue, L"%d", m_iSell[0] * m_iValue);
	TextOut(hDC, (int)(m_tRect.left + 244 + tPos.fX), (int)(m_tRect.top + 342 + tPos.fY), tValue, lstrlen(tValue));
	swprintf_s(tValue, L"%d", m_iSell[1] * m_iValue);
	TextOut(hDC, (int)(m_tRect.left + 565 + tPos.fX), (int)(m_tRect.top + 342 + tPos.fY), tValue, lstrlen(tValue));
	swprintf_s(tValue, L"%d", m_iSell[2] * m_iValue);
	TextOut(hDC, (int)(m_tRect.left + 708 + tPos.fX), (int)(m_tRect.top + 118 + tPos.fY), tValue, lstrlen(tValue));
	swprintf_s(tValue, L"%d", m_iSell[3] * m_iValue);
	TextOut(hDC, (int)(m_tRect.left + 708 + tPos.fX), (int)(m_tRect.top + 208 + tPos.fY), tValue, lstrlen(tValue));

	//244 342
	SelectObject(hDC, oldFont);
	DeleteObject(hFont);
}

void CShop::Release()
{
}
