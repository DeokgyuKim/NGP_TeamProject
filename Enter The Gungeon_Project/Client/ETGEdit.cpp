#include "stdafx.h"
#include "ETGEdit.h"
#include "Mouse.h"

#include "AbstractFactory.h"
#include "TileMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"


CETGEdit::CETGEdit()
	: m_bGuideLine(false)
{
}


CETGEdit::~CETGEdit()
{
	Release();
}

void CETGEdit::Initiailize()
{
	CTileMgr::Get_Instance()->Initialize();
	CObj* pObj = CAbstractFactory<CMouse>::Create();
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::MOUSE);
	m_dwTime = 0;
}

void CETGEdit::Update()
{
	CObjMgr::Get_Instance()->Update();
	POINT pt = {};
	pt.x = SCAST<LONG>(CObjMgr::Get_Instance()->Get_Mouse()->Get_Info()->fX - CScrollMgr::Get_MouseScroll().fX);
	pt.y = SCAST<LONG>(CObjMgr::Get_Instance()->Get_Mouse()->Get_Info()->fY - CScrollMgr::Get_MouseScroll().fY);

	if (CKeyMgr::Get_Instance()->KeyPressing('W'))
	{
		CScrollMgr::Set_Scroll(0, 20);
		CScrollMgr::Set_MouseScroll(0, 0);
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('A'))
	{
		CScrollMgr::Set_Scroll(20, 0);
		CScrollMgr::Set_MouseScroll(0, 0);
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('S'))
	{
		CScrollMgr::Set_Scroll(0, -20);
		CScrollMgr::Set_MouseScroll(0, 0);
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('D'))
	{
		CScrollMgr::Set_Scroll(-20, 0);
		CScrollMgr::Set_MouseScroll(0, 0);
	}

	if (CKeyMgr::Get_Instance()->KeyPressing(VK_LBUTTON))
	{
		if (m_dwTime + 300 < GetTickCount())
		{
			CTileMgr::Get_Instance()->PickingTile(pt, false);
			m_dwTime = GetTickCount();
		}
	}
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_RBUTTON))
	{
		if (m_dwTime + 300 < GetTickCount())
		{
			CTileMgr::Get_Instance()->PickingTile(pt, true);
			m_dwTime = GetTickCount();
		}
	}
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_NUMPAD8))
	{
		CTileMgr::Get_Instance()->PickingTile(pt, 9);
	}
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_NUMPAD6))
	{
		CTileMgr::Get_Instance()->PickingTile(pt, 11);
	}
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_NUMPAD2))
	{
		CTileMgr::Get_Instance()->PickingTile(pt, 12);
	}
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_NUMPAD4))
	{
		CTileMgr::Get_Instance()->PickingTile(pt, 10);
	}
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_NUMPAD5))
	{
		CTileMgr::Get_Instance()->PickingTile(pt, 30);
	}
	if (CKeyMgr::Get_Instance()->KeyPressing(VK_NUMPAD0))
	{
		CTileMgr::Get_Instance()->PickingTile(pt, 0);
	}

	if (CKeyMgr::Get_Instance()->KeyDown(VK_SPACE))
		CTileMgr::Get_Instance()->SaveData();
	if (CKeyMgr::Get_Instance()->KeyDown(VK_CONTROL))
	{
		CTileMgr::Get_Instance()->Clear();
		CTileMgr::Get_Instance()->LoadData();
	}
	if (CKeyMgr::Get_Instance()->KeyDown(VK_F12))
	{
		m_bGuideLine = !m_bGuideLine;
		cout << m_bGuideLine << endl;
	}
}

void CETGEdit::LateUpdate()
{
}

void CETGEdit::Render(HDC hDC)
{
	CTileMgr::Get_Instance()->Render(hDC, m_bGuideLine);
	CObjMgr::Get_Instance()->Render(hDC);
	
}

void CETGEdit::Release()
{
}
