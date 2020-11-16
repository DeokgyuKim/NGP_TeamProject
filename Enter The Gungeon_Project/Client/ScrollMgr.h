#pragma once
#include "stdafx.h"

class CScrollMgr
{
private:
	static POS m_tScrollMouse;
	static POS m_tScroll;
public:
	static void		Initialize(float fX, float fY) { m_tScroll.fX = fX; m_tScroll.fY = fY; }
	static POS		Get_Scroll() { return m_tScroll; }
	static POS		Get_MouseScroll() { return m_tScrollMouse; }
	static void		Set_Scroll(float fX, float fY) { m_tScroll.fX += fX; m_tScroll.fY += fY; Scroll_Lock(); }
	static void		Set_MouseScroll(float fX, float fY) { m_tScrollMouse.fX = m_tScroll.fX + fX; m_tScrollMouse.fY = m_tScroll.fY + fY; }
	static void		Scroll_Lock();
public:
	CScrollMgr() {}
	~CScrollMgr() {}
};