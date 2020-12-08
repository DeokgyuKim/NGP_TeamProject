#include "stdafx.h"
#include "TileMgr.h"
#include "Tile.h"

#include "AbstractFactory.h"

CTileMgr* CTileMgr::m_pInstance = NULL;

int * CTileMgr::Get_CullSize()
{
	int* iCull = new int[4];
	POS	tPos = CScrollMgr::Get_MouseScroll();
	if (tPos.fX > 0)
		tPos.fX = 0;
	if (tPos.fY > 0)
		tPos.fY = 0;
	iCull[0] = SCAST<int>(abs(tPos.fX / TILECX));
	iCull[1] = SCAST<int>(abs(tPos.fY / TILECY));

	//cout << iCullX << ", " << iCullY << endl;

	iCull[2] = iCull[0] + (WINCX / TILECX);
	iCull[3] = iCull[1] + (WINCY / TILECY);
	return iCull;
}

int * CTileMgr::Get_CullSize(INFO * pInfo, int iDist)
{
	int* iCull = new int[4];
	iCull[0] = SCAST<int>(abs(pInfo->fX / TILECX)) - iDist / 2;
	iCull[1] = SCAST<int>(abs(pInfo->fY / TILECY)) - iDist / 2;

	//cout << iCullX << ", " << iCullY << endl;

	iCull[2] = iCull[0] + iDist;
	iCull[3] = iCull[1] + iDist;
	return iCull;
}

void CTileMgr::Set_TileOption(int x, int y, int option)
{
	int iIndex = y * TILEX + x;
	CAST<CTile*>(m_vecTile[iIndex])->Set_Option(option);
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
			m_vecTile.emplace_back(pTile);
		}
	}
}

void CTileMgr::Render(HDC hDC, bool bGuideLine)
{
	POS	tPos = CScrollMgr::Get_MouseScroll();
	if (tPos.fX > 0)
		tPos.fX = 0;
	if (tPos.fY > 0)
		tPos.fY = 0;
	int iCullX = SCAST<int>(abs(tPos.fX / TILECX));
	int iCullY = SCAST<int>(abs(tPos.fY / TILECY));

	//cout << iCullX << ", " << iCullY << endl;

	int iCullEndX = iCullX + (WINCX / TILECX);
	int iCullEndY = iCullY + (WINCY / TILECY);

	for (int i = iCullY; i < iCullEndY + 2; ++i)
	{
		for (int j = iCullX; j < iCullEndX + 2; ++j)
		{
			int iIndex = j + (TILEX * i);
			if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
				continue;
			m_vecTile[iIndex]->Render(hDC);
#ifdef _DEBUG
			if (bGuideLine)
			{
				CAST<CTile*>(m_vecTile[iIndex])->Draw_GuideLine(hDC);
				TCHAR szPos[32] = L"";
				wsprintf(szPos, L"%d, %d", j, i);
				TextOut(hDC, (int)(m_vecTile[iIndex]->Get_Info()->fX + CScrollMgr::Get_MouseScroll().fX - 20)
					, (int)(m_vecTile[iIndex]->Get_Info()->fY + CScrollMgr::Get_MouseScroll().fY), szPos, lstrlen(szPos));
			}
#endif
		}
	}
}

void CTileMgr::Render(HDC hDC, int iC)
{
	POS	tPos = CScrollMgr::Get_MouseScroll();
	if (tPos.fX > 0)
		tPos.fX = 0;
	if (tPos.fY > 0)
		tPos.fY = 0;
	int iCullX = SCAST<int>(abs(tPos.fX / TILECX));
	int iCullY = SCAST<int>(abs(tPos.fY / TILECY));

	//cout << iCullX << ", " << iCullY << endl;

	int iCullEndX = iCullX + (WINCX / TILECX);
	int iCullEndY = iCullY + (WINCY / TILECY);

	for (int i = iCullY - 10; i < iCullEndY + 10; ++i)
	{
		for (int j = iCullX - 10; j < iCullEndX + 10; ++j)
		{
			int iIndex = j + TILEX * i;
			if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
				continue;
			if (CAST<CTile*>(m_vecTile[iIndex])->Get_DrawID() > 0 && CAST<CTile*>(m_vecTile[iIndex])->Get_DrawID() < 14)
				m_vecTile[iIndex]->Render(hDC);
		}
	}
}

void CTileMgr::RenderAll(HDC hDC, int iC)
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			int iIndex = j + TILEX * i;
			if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
				continue;
			if(CAST<CTile*>(m_vecTile[iIndex])->Get_DrawID() > 0 && CAST<CTile*>(m_vecTile[iIndex])->Get_DrawID() < 14)
				CAST<CTile*>(m_vecTile[iIndex])->Render(hDC, iC);
		}
	}
}

void CTileMgr::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), [](CObj*& pObj) {
		if (pObj) delete pObj;
		pObj = nullptr;
	});
}

void CTileMgr::PickingTile(POINT & rPt, bool bPlus)
{
	int iX = rPt.x / TILECX;
	int iY = rPt.y / TILECY;

	size_t iIndex = iX + (TILEX * iY);

	if (0 > iIndex || m_vecTile.size() <= iIndex)
		return;

	if (bPlus)
	{
		int iDrawID = CAST<CTile*>(m_vecTile[iIndex])->Get_DrawID() + 1;
		if (iDrawID >= 32)
			iDrawID = 0;
		CAST<CTile*>(m_vecTile[iIndex])->Set_DrawID(iDrawID);
		if (iDrawID < 15 || iDrawID == 31)
			CAST<CTile*>(m_vecTile[iIndex])->Set_Option(1);
		else
			CAST<CTile*>(m_vecTile[iIndex])->Set_Option(0);
		//cout << iDrawID << ", " << CAST<CTile*>(m_vecTile[iIndex])->Get_Option() << endl;
	}
	else
	{
		int iDrawID = CAST<CTile*>(m_vecTile[iIndex])->Get_DrawID() - 1;
		if (iDrawID < 0)
			iDrawID = 31;
		CAST<CTile*>(m_vecTile[iIndex])->Set_DrawID(iDrawID);
		if (iDrawID < 15 || iDrawID == 31)
			CAST<CTile*>(m_vecTile[iIndex])->Set_Option(1);
		else
			CAST<CTile*>(m_vecTile[iIndex])->Set_Option(0);
		//cout << iDrawID << ", " << CAST<CTile*>(m_vecTile[iIndex])->Get_Option() << endl;
	}
}

void CTileMgr::PickingTile(POINT & rPt, int DrawID)
{
	int iX = rPt.x / TILECX;
	int iY = rPt.y / TILECY;

	size_t iIndex = iX + (TILEX * iY);

	if (0 > iIndex || m_vecTile.size() <= iIndex)
		return;

	int iDrawID = DrawID;
	CAST<CTile*>(m_vecTile[iIndex])->Set_DrawID(iDrawID);
	if (iDrawID < 15 || iDrawID == 31)
		CAST<CTile*>(m_vecTile[iIndex])->Set_Option(1);
	else
		CAST<CTile*>(m_vecTile[iIndex])->Set_Option(0);
}

void CTileMgr::SaveData()
{
	HANDLE hFile = CreateFile(L"../Data/NgpTile.dat", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(nullptr, L"Save Failed!", L"SaveData", MB_OK);
		return;
	}
	DWORD	dwByte = 0;
	for (auto& pTile : m_vecTile)
	{
		int iDrawID = CAST<CTile*>(pTile)->Get_DrawID();
		int iOption = CAST<CTile*>(pTile)->Get_Option();
		WriteFile(hFile, pTile->Get_Info(), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
	}
	CloseHandle(hFile);
	MessageBox(nullptr, L"Save Success!", L"SaveData", MB_OK);
}

void CTileMgr::LoadData()
{
	HANDLE hFile = CreateFile(L"../Data/Tile.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(nullptr, L"Load Failed!", L"LoadData", MB_OK);
		return;
	}
	DWORD	dwByte = 0;
	INFO	tInfo = {};
	int		iDrawID = 0;
	int		iOption = 0;
	int iCount = 0;
	while(true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;
		CObj*	pObj = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY);
		CAST<CTile*>(pObj)->Set_DrawID(iDrawID);
		CAST<CTile*>(pObj)->Set_Option(iOption);
		m_vecTile.emplace_back(pObj);
	}
	CloseHandle(hFile);
	MessageBox(nullptr, L"Load Success!", L"LoadData", MB_OK);
}

void CTileMgr::LoadData(TCHAR * pChar)
{
	HANDLE hFile = CreateFile(pChar, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(nullptr, L"Load Failed!", L"LoadData", MB_OK);
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
		CAST<CTile*>(pObj)->Set_DrawID(iDrawID);
		CAST<CTile*>(pObj)->Set_Option(iOption);
		m_vecTile.emplace_back(pObj);
	}
	CloseHandle(hFile);
	MessageBox(nullptr, L"Load Success!", L"LoadData", MB_OK);
}

void CTileMgr::Clear()
{
	if (m_vecTile.empty())
		return;
	for (auto& pElement : m_vecTile)
		delete pElement;
	m_vecTile.clear();
}
