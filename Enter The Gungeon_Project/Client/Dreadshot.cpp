#include "stdafx.h"
#include "Dreadshot.h"


CDreadshot::CDreadshot()
{
}


CDreadshot::~CDreadshot()
{
	Release();
}

void CDreadshot::Initialize()
{
	m_tInfo.iCX = 1000;
	m_tInfo.iCY = 1000;
	iC = 0;
	m_pFrameKey = L"400";
}

int CDreadshot::Update()
{
	if (m_bDead && iC >= 1000)
		return OBJ_DEAD;
	iC += 100;
	return 0;
}

void CDreadshot::LateUpdate()
{
}

void CDreadshot::Render(HDC hDC)
{
	CObj::UpdateRect();
	POS tPos = CScrollMgr::Get_MouseScroll();
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(m_pFrameKey);
	GdiTransparentBlt(hDC, (int)(m_tInfo.fX - (iC / 2) + tPos.fX), (int)(m_tInfo.fY - (iC / 2) + tPos.fY), iC, iC, hMemDC, 0, 0, 400, 400, RGB(255, 0, 255));
	//Ellipse(hDC, m_tRect.left + tPos.fX, m_tRect.top + tPos.fY, m_tRect.right + tPos.fX, m_tRect.bottom + tPos.fY);
}

void CDreadshot::Release()
{
	//CEffectMgr::MakeEffect(L"BulletDieEffect", FRAME{ 0, 6, 0, 1, 100, 0 }, m_tInfo.fX, m_tInfo.fY, 27, 27);
}
