#include "stdafx.h"
#include "Shield.h"


CShield::CShield()
{
}


CShield::~CShield()
{
	Release(); 
}

void CShield::Initialize()
{
}

int CShield::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	return OBJ_NOEVENT;
}

void CShield::LateUpdate()
{
}

void CShield::Render(HDC hDC)
{
	CObj::UpdateRect(); 
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom); 
}

void CShield::Release()
{
}
