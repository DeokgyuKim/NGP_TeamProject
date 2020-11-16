//레이저 따로 오브젝트 충돌 만들기
#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
#include "Monster.h"
#include "RifleMonster.h"
#include "Wizard.h"
#include "Bird.h"
#include "Mouse.h"
#include "Gun.h"

#include "AbstractFactory.h"
#include "COllisionMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "UiMgr.h"
#include "BmpMgr.h"
#include "TileMgr.h"

CMainGame::CMainGame()
//	:m_pPlayer(nullptr)
	:m_iFPS(0)
	,m_szFPS(L"")
	, m_dwOldTime(0)
{
}

CMainGame::~CMainGame()
{
	Release(); 
}

void CMainGame::Initialize()
{
	ShowCursor(FALSE);
	CSoundMgr::Get_Instance()->Initialize();

	srand(unsigned(time(NULL)));
	m_hDC = GetDC(g_hWND);
	m_dwOldTime = GetTickCount();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Back/Back.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Back/BackBuffer.bmp", L"BackBuffer");

	CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_LOGO);


	//CObj* pObj = CAbstractFactory<CMouse>::Create();
	//CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::MOUSE);

	//pObj = CAbstractFactory<CPlayer>::Create();
	//CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::PLAYER);

	//pObj = CAbstractFactory<CGun>::CreateGun(nullptr, 40, 10, true);
	//pObj->Set_Pos(600, 500);
	//pObj->Set_Size(14, 14);
	//pObj->Set_Att(10);
	//CAST<CGun*>(pObj)->Set_GunType(GUN::NORMAL);
	//CAST<CGun*>(pObj)->Set_Speed(10.f);
	//CAST<CGun*>(pObj)->Set_BulletState(5, 0);
	//CAST<CGun*>(pObj)->Set_Time(1000, 200);
	//CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::GUN);

	//pObj = CAbstractFactory<CBird>::Create();
	//CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::MONSTER);
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
	//CObjMgr::Get_Instance()->Update(); 
}

void CMainGame::LateUpdate()
{
	CSceneMgr::Get_Instance()->LateUpdate();
	//CObjMgr::Get_Instance()->LateUpdate();
	CKeyMgr::Get_Instance()->UpdateState();
}

void CMainGame::Render()
{
	//Rectangle(m_hDC, 0, 0, WINCX * 2, WINCY * 2);
	//Rectangle(m_hDC, 100, 100, WINCX - 100, WINCY - 100);
	if (CSceneMgr::SCENE_INTRO == CSceneMgr::Get_Instance()->Get_SceneID() ||
		CSceneMgr::SCENE_ENDING == CSceneMgr::Get_Instance()->Get_SceneID())
		return;

	HDC hBack = CBmpMgr::Get_Instance()->Get_MemDC(L"Back");
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"BackBuffer");

	if (nullptr == hMemDC || nullptr == hBack)
		return;
	BitBlt(hBack, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	HPEN Pen, oPen;
	Pen = CreatePen(0, 2, RGB(255, 0, 0));
	oPen = (HPEN)SelectObject(hBack, Pen);
	
	CSceneMgr::Get_Instance()->Render(hBack);
#ifdef _DEBUG
	++m_iFPS;
	if (m_dwOldTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS: %d 세이브 스페이스바 / 로드 컨트롤", m_iFPS);
		m_iFPS = 0; 
		m_dwOldTime = GetTickCount();
	}
	TextOut(hBack, 100, 100, m_szFPS, lstrlen(m_szFPS));

	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);
	POS tPos = CScrollMgr::Get_MouseScroll();
	TCHAR pMouseCursor[32] = L"";
	swprintf_s(pMouseCursor, L"(%d , %d)", SCAST<int>(pt.x - tPos.fX), SCAST<int>(pt.y - tPos.fY));
	TextOut(hBack, 100, 150, pMouseCursor, lstrlen(pMouseCursor));

#endif

	SelectObject(hBack, oPen);
	DeleteObject(Pen);
	//CObjMgr::Get_Instance()->Render(hBack);
	BOOL b = BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBack, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{
	ReleaseDC(g_hWND, m_hDC);

	CObjMgr::Destroy_Instance();
	CBmpMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CSceneMgr::Destory_Instace();
	CUiMgr::Destroy_Instance();
	CTileMgr::Destroy_Instance();
}