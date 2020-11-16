#include "stdafx.h"
#include "Mouse.h"
#include "ScrollMgr.h"

CMouse::CMouse()
{
}


CMouse::~CMouse()
{
}

void CMouse::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Mouse/Aim.bmp", L"Aim");
	m_tInfo.iCX = 32; 
	m_tInfo.iCY = 32; 
}

int CMouse::Update()
{
	POINT pt = {}; 
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);
	m_tInfo.fX = float(pt.x);// -CScrollMgr::Get_Scroll().fX;
	m_tInfo.fY = static_cast<float>(pt.y);// -CScrollMgr::Get_Scroll().fY;
	return 0;
}

void CMouse::LateUpdate()
{

}

void CMouse::Render(HDC hDC)
{
	CObj::UpdateRect();
	POS tPos = CScrollMgr::Get_Scroll();
	//Ellipse(hDC, SCAST<int>(m_tRect.left + tPos.fX), SCAST<int>(m_tRect.top + tPos.fY), SCAST<int>(m_tRect.right + tPos.fX), SCAST<int>(m_tRect.bottom + tPos.fY));
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"Aim");
	//BitBlt(hDC, m_tRect.left + tPos.fX, m_tRect.top + tPos.fY, m_tInfo.iCX, m_tInfo.iCY, hMemDC, 0, 0, SRCCOPY);
	GdiTransparentBlt(hDC, SCAST<int>(m_tRect.left/* + tPos.fX*/), SCAST<int>(m_tRect.top/* + tPos.fY*/), m_tInfo.iCX, m_tInfo.iCY, hMemDC, 0, 0, m_tInfo.iCX, m_tInfo.iCY, RGB(255, 0, 255));
}

void CMouse::Release()
{
}
