#include "stdafx.h"
#include "KeyMgr.h"

CKeyMgr* CKeyMgr::m_pInstance = NULL;
bool CKeyMgr::KeyPressing(int iKey)
{
	if (GetAsyncKeyState(iKey) & 0x8000)
		return true;
	return false;
}

bool CKeyMgr::KeyDown(int iKey)
{
	if (GetAsyncKeyState(iKey) & 0x8000 && !m_bKeyState[iKey])
	{
		m_bKeyState[iKey] = !m_bKeyState[iKey];
		return true;
	}
	return false;
}

bool CKeyMgr::KeyUp(int iKey)
{
	if (!(GetAsyncKeyState(iKey) & 0x8000) && m_bKeyState[iKey])
	{
		m_bKeyState[iKey] = !m_bKeyState[iKey];
		return true;
	}
	return false;
}

void CKeyMgr::UpdateState()
{
	for (int i = 0; i < VK_MAX; ++i)
	{
		if (!m_bKeyState[i] && (GetAsyncKeyState(i) & 0x8000))	//이전에 안눌렸는데 현재 눌렀을 경우 바꿈
			m_bKeyState[i] = !m_bKeyState[i];
		if (m_bKeyState[i] && !(GetAsyncKeyState(i) & 0x8000))	//이전에 눌럿는데 현재 안눌렀을 경우 바꿈
			m_bKeyState[i] = !m_bKeyState[i];
	}
}