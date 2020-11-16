#pragma once
class CObj; 
class CCOllisionMgr
{
public:
	CCOllisionMgr();
	~CCOllisionMgr();
public:
	static void Collision_Bullet_Player(list<CObj*>* pBullets, CObj* pPlayer);
	static void Collision_Boom_Player(list<CObj*>* pBooms, CObj* pPlayer);
	static void Collision_Gun_Player(list<CObj*>* pGuns, CObj* pPlayer);
	static void Collision_Bullet_Monster(list<CObj*>* pBullets, list<CObj*>* pMonsters);
	static void Collision_Razer_Monster(list<CObj*>* pRazers, list<CObj*>* pMonsters);
	static void Collision_Razer_Desk(list<CObj*>* pRazers, list<CObj*>* pDesks);
	static void Collision_Dreadshot_Monster_Bullet(list<CObj*>* pDreadshots, list <CObj*>* pMonsters, list<CObj*>* pBullets);
	static void Collision_Desk_Bullet(list<CObj*>* pDesks, list<CObj*>* pBullets);
	static void Collision_Object_Desk(list<CObj*>* pObjs, list<CObj*>* pDesks);
	static void Collision_Object_Wall(list<CObj*>* pObjs, vector<CObj*>* pWalls);
	static void Collision_Bullet_Wall(list<CObj*>* pObjs, vector<CObj*>* pWalls);
	static void Collision_Shop_Player(CObj* pShop, CObj* pPlayer);
	static bool Collision_Shop_Bullet(RECT* pInfo, list<CObj*>* pBullets, list<CObj*>* pRazers);
	static void Collision_Shop_Buy(CObj* pShop, CObj* pPlayer);
	static bool Collision_Mouse_Teleport(CObj* pMouse, list<CObj*>* pTeleports, CObj* pPlayer);
	static void Collision_Player_BossStage(CObj* pPlayer);
	static bool CheckRazerWall(INFO* pRazer);
private:
	static bool CheckSphere(INFO* pDst, INFO* pSrc);
	static bool CheckSphereNRect(INFO* pInfo, RECT* pRect);
};

