#include "stdafx.h"
#include "BmpMgr.h"
#include "Bmp.h"


CBmpMgr* CBmpMgr::m_pInstance = NULL;
HDC CBmpMgr::Get_MemDC(const TCHAR * pKey)
{
	if (m_mapBmp.empty())
		return NULL;
	auto& iter = find_if(m_mapBmp.begin(), m_mapBmp.end(), [&](auto& rPair) {
		return !lstrcmp(rPair.first, pKey); });

	if (iter == m_mapBmp.end())
		return NULL;
	return iter->second->Get_MemDC();
}

HBITMAP CBmpMgr::Get_Bmp(const TCHAR * pKey)
{
	if (m_mapBmp.empty())
		return NULL;
	auto& iter = find_if(m_mapBmp.begin(), m_mapBmp.end(), [&](auto& rPair) {
		return !lstrcmp(rPair.first, pKey); });

	if (iter == m_mapBmp.end())
		return NULL;
	return iter->second->Get_Bmp();
}
void CBmpMgr::Insert_Bmp(const TCHAR * pPath, const TCHAR * pKey)
{
	auto& iter = find_if(m_mapBmp.begin(), m_mapBmp.end(), [&](auto& rPair) {
		return !lstrcmp(rPair.first, pKey); });
	if (m_mapBmp.end() == iter)
	{
		CBmp* pBmp = new CBmp;
		pBmp->Insert_Bmp(pPath);
		m_mapBmp.insert({ pKey, pBmp });
	}
}

void CBmpMgr::Release()
{
	for (auto& rPair : m_mapBmp)
	{
		if (rPair.second)
		{
			delete rPair.second;
			rPair.second = nullptr;
		}
	}
	m_mapBmp.clear();
}

CBmpMgr::CBmpMgr()
{
}


CBmpMgr::~CBmpMgr()
{
}
