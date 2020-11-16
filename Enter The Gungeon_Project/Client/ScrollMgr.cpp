#include "stdafx.h"
#include "ScrollMgr.h"

POS CScrollMgr::m_tScroll = {0, 0};
POS CScrollMgr::m_tScrollMouse = { 0, 0 };

void CScrollMgr::Scroll_Lock()
{
	if (0 < m_tScroll.fX)
		m_tScroll.fX = 0;
	if (0 < m_tScroll.fY)
		m_tScroll.fY = 0;
}
