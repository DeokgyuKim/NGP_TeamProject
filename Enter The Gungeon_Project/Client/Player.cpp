#include "stdafx.h"
#include "Player.h"
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

void CPlayer::Set_Roll(float fAngle)
{
	m_fSpeed += 15.f;
	m_bRoll = true;
	m_fRollAngle = fAngle;
}

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
	Release(); 
}

void CPlayer::Initialize()
{
	m_tInfo.fX = 1000;
	m_tInfo.fY = 800;
	CScrollMgr::Initialize(WINCX / 2 - m_tInfo.fX, WINCY / 2 - m_tInfo.fY);
	m_tInfo.iCX = 60;
	m_tInfo.iCY = 60;
	m_fSpeed = PLAYER_SPEED;
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

	/*m_vecGun.emplace_back(CAbstractFactory<CGun>::CreateGun(this, 40.f, 1, true));
	m_vecGun[m_iGunCount]->Set_Size(14, 14);
	m_vecGun[m_iGunCount]->Set_Att(10);
	++m_iGunCount;*/

	//pObj = CAbstractFactory<CGun>::CreateGun(this, 40.f, 5, true);
	//pObj->Set_Size(14, 14);
	//pObj->Set_Att(8);
	////pObj->Set_ID(OBJ::NORMAL);
	//CAST<CGun*>(pObj)->Set_GunType(GUN::AK);
	//CAST<CGun*>(pObj)->Set_Speed(20.f);
	//CAST<CGun*>(pObj)->Set_BulletState(30, 300);
	//CAST<CGun*>(pObj)->Set_Time(1000, 50);
	//m_vecGun.emplace_back(pObj);
	//++m_iGunCount;

	//pObj = CAbstractFactory<CGun>::CreateGun(this, 40.f, 15, true);
	//pObj->Set_Size(14, 14);
	//pObj->Set_Att(5);
	////pObj->Set_ID(OBJ::NORMAL);
	//CAST<CGun*>(pObj)->Set_GunType(GUN::UMP);
	//CAST<CGun*>(pObj)->Set_Speed(20.f);
	//CAST<CGun*>(pObj)->Set_BulletState(20, 400);
	//CAST<CGun*>(pObj)->Set_Time(1000, 20);
	//m_vecGun.emplace_back(pObj);
	//++m_iGunCount;

	//

	//pObj = CAbstractFactory<CChargegun>::CreateGun(this, 40.f, 0, true);
	//pObj->Set_Size(14, 14);
	////pObj->Set_ID(OBJ::CHARGE);
	//pObj->Set_Att(5);
	//CAST<CGun*>(pObj)->Set_GunType(GUN::RAZER);
	//CAST<CGun*>(pObj)->Set_Speed(10.f);
	//CAST<CGun*>(pObj)->Set_BulletState(1, 100);
	//CAST<CGun*>(pObj)->Set_Time(1000, 0);
	//m_vecGun.emplace_back(pObj);
	//++m_iGunCount;

	//pObj = CAbstractFactory<CRazer>::CreateGun(this, 40.f, 10, true);
	//pObj->Set_Size(14, 14);
	////pObj->Set_ID(OBJ::RAZER);
	//CAST<CGun*>(pObj)->Set_GunType(GUN::RAZER);
	//pObj->Set_Att(1);
	//CAST<CGun*>(pObj)->Set_Speed(10.f);
	//CAST<CGun*>(pObj)->Set_BulletState(5, 100);
	//CAST<CGun*>(pObj)->Set_Time(1000, 800);
	//m_vecGun.emplace_back(pObj);
	//++m_iGunCount;

	m_pState = new StateMachine<CPlayer>(this);
	m_pState->SetCurrentState(CPlayerState_IDLE::Instance());

	Set_Frame(0, 3, 0, 100);
	Set_Frame_Plus(true);
	Set_FrameKey(L"Player_Down");
	m_bCheat = false;
}

int CPlayer::Update()
{
	//cout << m_iGold << endl;
	if (m_bDead && !m_bCheat)
		return OBJ_PLAYERDEAD;

	if (CKeyMgr::Get_Instance()->KeyDown(VK_F1))
		m_bCheat = true;
	if (CKeyMgr::Get_Instance()->KeyDown(VK_F2))
		m_iGold += 10;

	if (m_bDamaged)
	{
		if (m_dwTime + 1000 < GetTickCount())
		{
			m_bDamaged = false;
		}
	}
	m_pState->Update();

	//플레이어와 마우스 각도 계산
	float fX = (m_pMouse->Get_Info()->fX - CScrollMgr::Get_Scroll().fX) - m_tInfo.fX;
	float fY = (m_pMouse->Get_Info()->fY - CScrollMgr::Get_Scroll().fY) - m_tInfo.fY;
	float fDist = sqrtf(fX * fX + fY * fY);

	float fAngle = acosf(fX / fDist);
	m_fAngle = RADIANTODEGREE(fAngle);
	if (m_tInfo.fY < m_pMouse->Get_Info()->fY - CScrollMgr::Get_Scroll().fY)
		m_fAngle = 360.f - m_fAngle;
	//cout << m_fAngle << endl;

	fAngle = 0.f;
	if (m_bRoll)
		fAngle = m_fRollAngle;
	else
		fAngle = m_fAngle;
	if(0 + 22.5f < fAngle && fAngle <= 45 + 22.5f)
		m_pFrameKey = (L"Player_RightUp");
	else if(45 + 22.5f < fAngle && fAngle <= 90 + 22.5f)
		m_pFrameKey = (L"Player_Up");
	else if (90 + 22.5f < fAngle && fAngle <= 135 + 22.5f)
		m_pFrameKey = (L"Player_LeftUp");
	else if (135 + 22.5f < fAngle && fAngle <= 180 + 22.5f)
		m_pFrameKey = (L"Player_Left");
	else if (180 + 22.5f < fAngle && fAngle <= 225 + 22.5f)
		m_pFrameKey = (L"Player_LeftDown");
	else if (225 + 22.5f < fAngle && fAngle <= 270 + 22.5f)
		m_pFrameKey = (L"Player_Down");
	else if (270 + 22.5f < fAngle && fAngle <= 315 + 22.5f)
		m_pFrameKey = (L"Player_RightDown");
	else
		m_pFrameKey = (L"Player_Right");
	m_vecGun[m_iGunNow]->Update();


	return OBJ_NOEVENT;
}

void CPlayer::LateUpdate()
{
	m_vecGun[m_iGunNow]->LateUpdate();
	SetOffset();
	CObj::FrameMove();
}

void CPlayer::Render(HDC hDC)
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

void CPlayer::Release()
{
	for (auto& pElement : m_vecGun)
	{
		pElement->Release();
		delete pElement;
	}
}

void CPlayer::KeyDown()
{
	if (CKeyMgr::Get_Instance()->KeyPressing('W'))
	{
		if (m_bRoll == false)
			m_tInfo.fY -= m_fSpeed;
		if (CKeyMgr::Get_Instance()->KeyDown(VK_RBUTTON))
		{
			Set_Roll(90.f);
		}
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('A'))
	{
		if (m_bRoll == false)
			m_tInfo.fX -= m_fSpeed;
		if (CKeyMgr::Get_Instance()->KeyDown(VK_RBUTTON))
		{
			Set_Roll(180.f);
		}
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('S'))
	{
		if (m_bRoll == false)
			m_tInfo.fY += m_fSpeed;
		if (CKeyMgr::Get_Instance()->KeyDown(VK_RBUTTON))
		{
			Set_Roll(270.f);
		}
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('D'))
	{
		if (m_bRoll == false)
			m_tInfo.fX += m_fSpeed;
		if (CKeyMgr::Get_Instance()->KeyDown(VK_RBUTTON))
		{
			Set_Roll(0.f);
		}
	}
	CAST<CGun*>(m_vecGun[m_iGunNow])->KeyDown();
	if (CKeyMgr::Get_Instance()->KeyDown('R'))
	{
		if (m_bRoll == false)
		{
			CAST<CGun*>(m_vecGun[m_iGunNow])->Reload();
		}
	}
}

void CPlayer::SetOffset()
{
	POS tScroll = CScrollMgr::Get_Scroll();
	if ((WINCX / 2) > m_tInfo.fX + tScroll.fX)
		CScrollMgr::Set_Scroll(m_fSpeed, 0);
	if ((WINCX / 2) < m_tInfo.fX + tScroll.fX)
		CScrollMgr::Set_Scroll(-m_fSpeed, 0);
	if ((WINCY / 2) > m_tInfo.fY + tScroll.fY)
		CScrollMgr::Set_Scroll(0, m_fSpeed);
	if ((WINCY / 2) < m_tInfo.fY + tScroll.fY)
		CScrollMgr::Set_Scroll(0, -m_fSpeed);
	POS	  tPosMouse = { m_pMouse->Get_Info()->fX, m_pMouse->Get_Info()->fY };
	if (tPosMouse.fX > WINCX)
		tPosMouse.fX = WINCX;
	if (tPosMouse.fY > WINCY)
		tPosMouse.fY = WINCY;
	float fPlusX = ((tPosMouse.fX - CScrollMgr::Get_Scroll().fX) - m_tInfo.fX) / 2;
	float fPlusY = ((tPosMouse.fY - CScrollMgr::Get_Scroll().fY) - m_tInfo.fY) / 2;
	//CScrollMgr::Initialize(CScrollMgr::Get_Scroll().fX - fPlusX, CScrollMgr::Get_Scroll().fY - fPlusY);
	//cout << m_tInfo.fX << ", " << m_tInfo.fY << " / " << CScrollMgr::Get_Scroll().fX << ", " << CScrollMgr::Get_Scroll().fY << endl;
	tScroll = CScrollMgr::Get_Scroll();
	if (m_tInfo.fX + tScroll.fX <= WINCX / 2 + m_fSpeed && m_tInfo.fX + tScroll.fX >= WINCX / 2 - m_fSpeed)
		CScrollMgr::Initialize(WINCX / 2 - m_tInfo.fX, tScroll.fY);
	tScroll = CScrollMgr::Get_Scroll();
	if (m_tInfo.fY + tScroll.fY <= WINCY / 2 + m_fSpeed && m_tInfo.fY + tScroll.fY >= WINCY / 2 - m_fSpeed )
		CScrollMgr::Initialize(tScroll.fX, WINCY / 2 - m_tInfo.fY);
	
	//if (fPlusX > 600)
	//	fPlusX = 600;
	//else if (fPlusX < -600)
	//	fPlusX = -600;
	//if (fPlusY > 600)
	//	fPlusY = 600;
	//else if (fPlusY < -600)
	//	fPlusY = -600;

	CScrollMgr::Set_MouseScroll(-fPlusX / 2, -fPlusY / 2);
	////if (fabs(m_tInfo.fX - (m_pMouse->Get_Info()->fX) + CScrollMgr::Get_Scroll().fX) < WINCX - 200)
	//{
	//	float fX = (m_pMouse->Get_Info()->fX + CScrollMgr::Get_Scroll().fX - m_tInfo.fX) / 2;
	//	CScrollMgr::Set_Scroll(-fX, 0);
	//}
	////if (fabs(m_tInfo.fY - (m_pMouse->Get_Info()->fY) + CScrollMgr::Get_Scroll().fY) < WINCY - 200)
	//{
	//	float fY = (m_pMouse->Get_Info()->fY + CScrollMgr::Get_Scroll().fY - m_tInfo.fY) / 2;
	//	CScrollMgr::Set_Scroll(0, -fY);
	//}
	//cout << CScrollMgr::Get_Scroll().fX << " / " << CScrollMgr::Get_Scroll().fY << endl;
}

void CPlayer::CreateDreadShot()
{
	if (m_iDreadshot <= 0)
		return;
	CObj* pObj = new CDreadshot();
	pObj->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	pObj->Initialize();
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::DREADSHOT);
	--m_iDreadshot;
}
