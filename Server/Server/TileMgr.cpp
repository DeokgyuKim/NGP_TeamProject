#include <algorithm>
#include "define.h"
#include "TileMgr.h"
#include "Tile.h"

#include "AbstractFactory.h"

#include <iostream>

CTileMgr* CTileMgr::m_pInstance = NULL;

int * CTileMgr::Get_CullSize(float fX, float fY, int iDist)
{
	int* iCull = new int[4];
	iCull[0] = static_cast<int>(abs(fX / TILECX)) - iDist / 2;
	iCull[1] = static_cast<int>(abs(fY / TILECY)) - iDist / 2;

	//cout << iCullX << ", " << iCullY << endl;

	iCull[2] = iCull[0] + iDist;
	iCull[3] = iCull[1] + iDist;
	return iCull;
}

void CTileMgr::Set_TileOption(int x, int y, int option)
{
	int iIndex = y * TILEX + x;
	static_cast<CTile*>(m_vecTile[iIndex])->Set_Option(option);
}

void CTileMgr::Initialize()
{
	for (int i = 0; i < TILEY; ++i)
	{
		float fY = float((TILECY * i) + (TILECY >> 1));
		for (int j = 0; j < TILEX; ++j)
		{
			float fX = float((TILECX * j) + (TILECX >> 1));

			CObj* pTile = CAbstractFactory<CTile>::Create(fX, fY);
			pTile->UpdateRect();
			m_vecTile.emplace_back(pTile);
		}
	}
}

void CTileMgr::Release()
{
	for (auto& pElement : m_vecTile)
		delete pElement;
	m_vecTile.clear();
}

void CTileMgr::LoadData(TCHAR * pChar)
{
	HANDLE hFile = CreateFile(pChar, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		cout << "Tile Load Failed" << endl;
		return;
	}
	DWORD	dwByte = 0;
	INFO	tInfo = {};
	int		iDrawID = 0;
	int		iOption = 0;
	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;
		CObj*	pObj = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY);
		pObj->UpdateRect();
		static_cast<CTile*>(pObj)->Set_DrawID(iDrawID);
		static_cast<CTile*>(pObj)->Set_Option(iOption);
		m_vecTile.emplace_back(pObj);
	}
	cout << "Tile Load Success" << endl;
	CloseHandle(hFile);
}

void CTileMgr::Clear()
{
	if (m_vecTile.empty())
		return;
	for (auto& pElement : m_vecTile)
		delete pElement;
	m_vecTile.clear();
}
