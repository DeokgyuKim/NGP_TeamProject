#include "stdafx.h"
#include "ETGStage.h"

#include "Mouse.h"
#include "Player.h"
#include "OtherPlayer.h"
#include "Tile.h"
#include "Monster.h"
#include "RifleMonster.h"
#include "Wizard.h"
#include "Bird.h"
#include "Gun.h"
#include "OtherGun.h"
#include "Desk.h"
#include "Box.h"
#include "Shop.h"
#include "Ground.h"
#include "Door.h"
#include "Teleport.h"

#include "COllisionMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "TileMgr.h"
#include "UiMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

#include "NetWork.h"

CETGStage::CETGStage()
	:m_bMapOn(false)
{
}


CETGStage::~CETGStage()
{
	Release();
}

void CETGStage::Initiailize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Player/Player_Left.bmp", L"Player_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Player/Player_LeftDown.bmp", L"Player_LeftDown");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Player/Player_Down.bmp", L"Player_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Player/Player_RightDown.bmp", L"Player_RightDown");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Player/Player_Right.bmp", L"Player_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Player/Player_RightUp.bmp", L"Player_RightUp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Player/Player_Up.bmp", L"Player_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Player/Player_LeftUp.bmp", L"Player_LeftUp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Player/HPFullUI.bmp", L"HPFullUI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Player/HPHalfUI.bmp", L"HPHalfUI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Player/Dreadshot.bmp", L"Dreadshot");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Bullet/NormalBullet.bmp", L"NormalBullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Bullet/MonsterBulletRed.bmp", L"RazerBullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Bullet/MonsterBulletBlue.bmp", L"ChargeBullet");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Gun/BlueBulletUI.bmp", L"BlueBulletUI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Gun/NormalBulletUI.bmp", L"NormalBulletUI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Gun/RedBulletUI.bmp", L"RedBulletUI");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Monster/MonsterDie.bmp", L"MonsterDie");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Monster/MonsterDie2.bmp", L"MonsterDie2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Monster/MonsterInit.bmp", L"MonsterInit");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Object/Table/Table.bmp", L"Table");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Object/Table/TableDown.bmp", L"TableDown");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Object/Table/TableLeft.bmp", L"TableLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Object/Table/TableRight.bmp", L"TableRight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Object/Table/TableUp.bmp", L"TableUp");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Object/ItemBox1.bmp", L"ItemBox1");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Object/DownDoor1.bmp", L"DownDoor1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Object/UpDoor1.bmp", L"UpDoor1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Object/LeftDoor1.bmp", L"LeftDoor1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Object/RightDoor1.bmp", L"RightDoor1");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Effect/BulletDieEffect.bmp", L"BulletDieEffect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Effect/BulletOutEffect.bmp", L"BulletOutEffect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Effect/PlayerJumpingEffect.bmp", L"PlayerJumpingEffect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Effect/PlayerWalkingEffect.bmp", L"PlayerWalkingEffect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Effect/400.bmp", L"400");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Gun/RemainingBulletZeroUI.bmp", L"RemainingBulletZeroUI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Gun/RemainingBulletMaxUI.bmp", L"RemainingBulletMaxUI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Gun/ReloadingBar.bmp", L"ReloadingBar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Gun/ReloadingStick.bmp", L"ReloadingStick");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Monster/MonsterGunLeft.bmp", L"MonsterGunLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Monster/MonsterGunRight.bmp", L"MonsterGunRight");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Gun/AkLeft.bmp", L"AkLeft");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Gun/AkRight.bmp", L"AkRight");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Gun/ShotgunLeft.bmp", L"ShotgunLeft");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Gun/ShotgunRight.bmp", L"ShotgunRight");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Gun/UmpLeft.bmp", L"UmpLeft");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Gun/UmpRight.bmp", L"UmpRight");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/MapTile/MinimapFrameUI.bmp", L"MinimapFrameUI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/MapTile/MinimapBoardUI.bmp", L"MinimapBoardUI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/MapTile/BigMap.bmp", L"BigMap");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/MapTile/BigMapSec.bmp", L"BigMapSec");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/MapTile/BigMapSecBack.bmp", L"BigMapSecBack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/MapTile/MapBuffer.bmp", L"MapBuffer");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/MapTile/MapBufferBack.bmp", L"MapBufferBack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/MapTile/TwinkleTile.bmp", L"TwinkleTile");
	

	
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/MapTile/MapTileSmall.bmp", L"MapTileSmall");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/MapTile/PlayerMapUI.bmp", L"PlayerMapUI");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/MapTile/TeleportOffTile.bmp", L"TeleportOffTile");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/MapTile/TeleportTile.bmp", L"TeleportTile");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/MapTile/PlayerMapUI.bmp", L"PlayerMapUI");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Gun/BlueBulletUI.bmp", L"BlueBulletUI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Gun/RedBulletUI.bmp", L"RedBulletUI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Gun/NormalBulletUI.bmp", L"NormalBulletUI");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/GunRotate/AkLeft.bmp", L"AkLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/GunRotate/AkRight.bmp", L"AkRight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/GunRotate/UmpLeft.bmp", L"UmpLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/GunRotate/UmpRight.bmp", L"UmpRight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/GunRotate/ChargeLeft.bmp", L"ChargeLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/GunRotate/ChargeRight.bmp", L"ChargeRight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/GunRotate/NormalLeft.bmp", L"NormalLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/GunRotate/NormalRight.bmp", L"NormalRight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/GunRotate/RazerLeft.bmp", L"RazerLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/GunRotate/RazerRight.bmp", L"RazerRight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/GunRotate/ShotgunLeft.bmp", L"ShotgunLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/GunRotate/ShotgunRight.bmp", L"ShotgunRight");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Resource/Image/Shop/Shop.bmp", L"Shop");


	CObj* pObj = CAbstractFactory<CMouse>::Create();
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::MOUSE);

	pObj = CAbstractFactory<CPlayer>::Create();
	CPlayer* pPlayer = static_cast<CPlayer*>(pObj);
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::PLAYER);

	//pObj = CAbstractFactory<CGun>::CreateGun(nullptr, 40, 10, true);
	//pObj->Set_Pos(600, 500);
	//pObj->Set_Size(14, 14);
	//pObj->Set_Att(10);
	//CAST<CGun*>(pObj)->Set_GunType(GUN::NORMAL);
	//CAST<CGun*>(pObj)->Set_Speed(10.f);
	//CAST<CGun*>(pObj)->Set_BulletState(5, 0);
	//CAST<CGun*>(pObj)->Set_Time(1000, 200);
	//CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::GUN);

	//pObj = CAbstractFactory<CBird>::Create(100.f, 100.f);
	//CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::MONSTER);

	//pObj = CAbstractFactory<CWizard>::Create(300.f, 300.f);
	//CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::MONSTER);

	//pObj = CAbstractFactory<CRifleMonster>::Create(500.f, 500.f);
	//CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::MONSTER);

	//pObj = CAbstractFactory<CMonster>::Create(3600.f, 1000.f);
	//CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::MONSTER);

	pObj = CAbstractFactory<CShop>::Create();
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::SHOP);

	//CEffectMgr::MakeEffectMonsterInit(L"MonsterInit", FRAME(0, 5, 0, 1, 150, 0), 3300.f, 1000.f, 70, 70, OBJ::NORMAL);

	pObj = CAbstractFactory<CDesk>::Create(3300.f, 1000.f);
	CAST<CDesk*>(pObj)->UpdateCollisionRect();
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::DESK);

	pObj = CAbstractFactory<CDesk>::Create(3600.f, 1000.f);
	CAST<CDesk*>(pObj)->UpdateCollisionRect();
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::DESK);

	pObj = CAbstractFactory<CDesk>::Create(85.f * TILECX, 10.f * TILECY);
	CAST<CDesk*>(pObj)->UpdateCollisionRect();
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::DESK);

	pObj = CAbstractFactory<CDesk>::Create(78.f * TILECX, 39.f * TILECY);
	CAST<CDesk*>(pObj)->UpdateCollisionRect();
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::DESK);

	pObj = CAbstractFactory<CDesk>::Create(78.f * TILECX, 57.f * TILECY);
	CAST<CDesk*>(pObj)->UpdateCollisionRect();
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::DESK);

	CTileMgr::Get_Instance()->LoadData(L"../Data/StageTile.dat");
	//for (auto& pTile : *CTileMgr::Get_Instance()->Get_Tile())
	//{
	//	if (CAST<CTile*>(pTile)->Get_Option() == 1)
	//	{
	//		CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::WALL);
	//	}
	//}
	pObj = CAbstractFactory<CGround>::Create();
	CAST<CGround*>(pObj)->Set_Rect(43, 6, 66, 26);
	CAST<CGround*>(pObj)->Make_Door(41, 16, DOOR::LEFT);
	CAST<CGround*>(pObj)->Make_Door(41, 24, DOOR::LEFT);
	CAST<CGround*>(pObj)->Make_Door(49, 27, DOOR::BOTTOM);
	CAST<CGround*>(pObj)->Make_Door(67, 9, DOOR::RIGHT);
	CAST<CGround*>(pObj)->Make_Tele(53, 17);
	CAST<CGround*>(pObj)->Push_Pos(POS{ 47, 12 }, OBJ::NORMAL);
	CAST<CGround*>(pObj)->Push_Pos(POS{ 53, 12 }, OBJ::RIFLE);
	CAST<CGround*>(pObj)->Push_Pos(POS{ 59, 12 }, OBJ::NORMAL);
	CAST<CGround*>(pObj)->Push_Pos(POS{ 47, 19 }, OBJ::NORMAL);
	CAST<CGround*>(pObj)->Push_Pos(POS{ 53, 19 }, OBJ::RIFLE);
	CAST<CGround*>(pObj)->Push_Pos(POS{ 59, 19 }, OBJ::NORMAL);
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::GROUND);

	pObj = CAbstractFactory<CGround>::Create();
	CAST<CGround*>(pObj)->Set_Rect(82, 6, 98, 23);
	CAST<CGround*>(pObj)->Make_Door(80, 9, DOOR::LEFT);
	CAST<CGround*>(pObj)->Push_Pos(POS{ 89, 8 }, OBJ::NORMAL);
	CAST<CGround*>(pObj)->Push_Pos(POS{ 89, 11 }, OBJ::RIFLE);
	CAST<CGround*>(pObj)->Push_Pos(POS{ 89, 14 }, OBJ::BIRD);
	CAST<CGround*>(pObj)->Push_Pos(POS{ 89, 17 }, OBJ::NORMAL);
	CAST<CGround*>(pObj)->Push_Pos(POS{ 89, 20 }, OBJ::RIFLE);
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::GROUND);

	pObj = CAbstractFactory<CGround>::Create();
	CAST<CGround*>(pObj)->Set_Rect(36, 39, 53, 70);
	CAST<CGround*>(pObj)->Make_Door(49, 37, DOOR::TOP);
	CAST<CGround*>(pObj)->Make_Door(54, 49, DOOR::RIGHT);
	CAST<CGround*>(pObj)->Make_Tele(44, 56);

	CAST<CGround*>(pObj)->Push_Pos(POS{ 39, 45 }, OBJ::NORMAL);
	CAST<CGround*>(pObj)->Push_Pos(POS{ 49, 45 }, OBJ::NORMAL);
	CAST<CGround*>(pObj)->Push_Pos(POS{ 39, 49 }, OBJ::RIFLE);
	CAST<CGround*>(pObj)->Push_Pos(POS{ 49, 49 }, OBJ::RIFLE);
	CAST<CGround*>(pObj)->Push_Pos(POS{ 39, 53 }, OBJ::WIZARD);
	CAST<CGround*>(pObj)->Push_Pos(POS{ 49, 53 }, OBJ::WIZARD);
	CAST<CGround*>(pObj)->Push_Pos(POS{ 39, 57 }, OBJ::RIFLE);
	CAST<CGround*>(pObj)->Push_Pos(POS{ 49, 57 }, OBJ::RIFLE);
	CAST<CGround*>(pObj)->Push_Pos(POS{ 39, 61 }, OBJ::BIRD);
	CAST<CGround*>(pObj)->Push_Pos(POS{ 49, 61 }, OBJ::BIRD);
	CAST<CGround*>(pObj)->Push_Pos(POS{ 39, 65 }, OBJ::NORMAL);
	CAST<CGround*>(pObj)->Push_Pos(POS{ 49, 66 }, OBJ::NORMAL);

	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::GROUND);

	pObj = CAbstractFactory<CGround>::Create();
	CAST<CGround*>(pObj)->Set_Rect(65, 35, 91, 62);
	CAST<CGround*>(pObj)->Make_Door(63, 49, DOOR::LEFT);
	CAST<CGround*>(pObj)->Make_Door(92, 48, DOOR::RIGHT);

	int iCount = 0;
	for (int j = 39; j <= 59; j += 8)
	{
		for (int i = 69; i <= 88; i += 8)
		{
			CAST<CGround*>(pObj)->Push_Pos(POS{ SCAST<float>(i), SCAST<float>(j) }, SCAST<OBJ::TYPE>(iCount));
			iCount = (iCount + 1) % 4;
		}
	}

	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::GROUND);


	pObj = CAbstractFactory<CBox>::Create(3600.f, 480.f);
	CAST<CBox*>(pObj)->Set_BoxType(GUN::UMP);
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::MONSTER);

	pObj = CAbstractFactory<CBox>::Create(5760.f, 420.f);
	CAST<CBox*>(pObj)->Set_BoxType(GUN::AK);
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::MONSTER);

	pObj = CAbstractFactory<CBox>::Create(2850.f, 4420.f);
	CAST<CBox*>(pObj)->Set_BoxType(GUN::SHOTGUN);
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::MONSTER);

	char szIp[30];
	cin >> szIp;
	CNetwork::GetInstance()->Init(szIp);

	pObj = CAbstractFactory<COtherPlayer>::Create();
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::OTHERPLAYER);

	pObj = CAbstractFactory<COtherGun>::Create();
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::OTHERGUN);


	static_cast<CGun*>(pPlayer->Get_GunNow())->m_iPlayerNum;
	if (CNetwork::GetInstance()->m_iPlayerNum == 0)
		static_cast<COtherGun*>(pObj)->m_iPlayerNum = 1;
	else
		static_cast<COtherGun*>(pObj)->m_iPlayerNum = 0;

}

void CETGStage::Update()
{
	if (!m_bMapOn)
	{
		CObjMgr::Get_Instance()->Update();
		//if (CKeyMgr::Get_Instance()->KeyDown(VK_F11))
		//	CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_BOSS);
		if (CObjMgr::Get_Instance()->Get_Player()->Get_Hp() <= 0)
		{
			CNetwork::GetInstance()->m_iWin = -1;
			CNetwork::GetInstance()->m_bServerOn = false;
			cout << "ÆÐ¹è" << endl;
			CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_ENDING);
		}
		else if (CObjMgr::Get_Instance()->Get_Other()->front()->Get_Hp() <= 0)
		{
			CNetwork::GetInstance()->m_iWin = 1;
			CNetwork::GetInstance()->m_bServerOn = false;
			cout << "½Â¸®" << endl;
			CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_ENDING);
		}
	}
	else
	{
		CObjMgr::Get_Instance()->Get_Mouse()->Update();
	}
	if (CKeyMgr::Get_Instance()->KeyDown(VK_TAB))
	{
		m_bMapOn = !m_bMapOn;
		CUiMgr::Get_Instance()->Set_MapOn(m_bMapOn);
	}
}

void CETGStage::LateUpdate()
{
	if (!m_bMapOn)
	{
		CObjMgr::Get_Instance()->LateUpdate();
	}
	else
	{
		CObjMgr::Get_Instance()->Get_Mouse()->Update();
		if (CCOllisionMgr::Collision_Mouse_Teleport(CObjMgr::Get_Instance()->Get_Mouse(), CObjMgr::Get_Instance()->Get_Teleport(), CObjMgr::Get_Instance()->Get_Player()))
		{
			CSoundMgr::Get_Instance()->PlaySound(L"portal.mp3", CSoundMgr::MAXCHANNEL);
			m_bMapOn = false;
		}
	}
	CNetwork::GetInstance()->Update();
	CSoundMgr::Get_Instance()->Update();
}

void CETGStage::Render(HDC hDC)
{
	if (!m_bMapOn)
	{
		CTileMgr::Get_Instance()->Render(hDC, false);
		CObjMgr::Get_Instance()->Render(hDC);
		CUiMgr::Get_Instance()->Render(hDC);
		CObjMgr::Get_Instance()->Get_Mouse()->Render(hDC);
	}
	else
	{
		HDC MapBuffer = CBmpMgr::Get_Instance()->Get_MemDC(L"MapBuffer");		

		CTileMgr::Get_Instance()->RenderAll(MapBuffer, 8);
		CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();

		HDC hPlayerUi = CBmpMgr::Get_Instance()->Get_MemDC(L"PlayerMapUI");	

		GdiTransparentBlt(hDC, 0, 0, 1280, 800, MapBuffer, 0, 0, 1280, 800, RGB(255, 0, 255));


		for (auto& iter : *CObjMgr::Get_Instance()->Get_Teleport())
		{
			CAST<CTeleport*>(iter)->RenderMap(hDC, 8);
		}

		GdiTransparentBlt(hDC, (int)(pPlayer->Get_Info()->fX / 8 + MAPFIXX), (int)(pPlayer->Get_Info()->fY / 8 + MAPFIXY),
			10, 10, hPlayerUi, 0, 0, 40, 40, RGB(255, 0, 255));
		CObjMgr::Get_Instance()->Get_Mouse()->Render(hDC);
	}
}

void CETGStage::Release()
{
	for (int i = 0; i < OBJ::END; ++i)
	{
		if (i == OBJ::PLAYER || i == OBJ::MOUSE || i == OBJ::GROUND || i == OBJ::DOOR)
			continue;
		CObjMgr::Get_Instance()->Clear_Object(SCAST<OBJ::ID>(i));
	}
}
