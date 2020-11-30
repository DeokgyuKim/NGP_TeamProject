#include "stdafx.h"
#include "COllisionMgr.h"
#include "Obj.h"
#include "Player.h"
#include "Gun.h"
#include "Monster.h"
#include "RifleMonster.h"
#include "Wizard.h"
#include "Bird.h"
#include "Boss.h"
#include "Desk.h"
#include "Tile.h"
#include "Shop.h"
#include "Chargegun.h"
#include "Razer.h"
#include "Teleport.h"

#include "PlayerState.h"
#include "MonsterState.h"
#include "RifleMonsterState.h"
#include "WizardState.h"
#include "BirdState.h"
#include "BossState.h"

#include "SceneMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "TileMgr.h"
#include "KeyMgr.h"


CCOllisionMgr::CCOllisionMgr()
{
}


CCOllisionMgr::~CCOllisionMgr()
{
}

void CCOllisionMgr::Collision_Bullet_Player(list<CObj*>* pBullets, CObj * pPlayer)
{
	if (pBullets->empty())
		return;
	if (CAST<CPlayer*>(pPlayer)->Get_FSM()->GetCurrentState() == CPlayerState_ROLL::Instance())
		return;
	if (CAST<CPlayer*>(pPlayer)->Get_Damaged())
		return;
	for (auto& pElement : *pBullets)
	{
		RECT rc = {};
		if (fabs(pElement->Get_Info()->fX - pPlayer->Get_Info()->fX) > 100)
			continue;
		if(IntersectRect(&rc, pPlayer->Get_Rect(), pElement->Get_Rect()))
		//if (CheckSphereNRect(pElement->Get_Info(), pPlayer->Get_Rect()))
		{
			CAST<CPlayer*>(pPlayer)->Set_Damaged();
			pPlayer->Set_Hp(pPlayer->Get_Hp() - pElement->Get_Att());
			if (pPlayer->Get_Hp() <= 0)
				pPlayer->Set_Dead();
			pElement->Set_Dead();
			return;
		}
	}
}

void CCOllisionMgr::Collision_Boom_Player(list<CObj*>* pBooms, CObj * pPlayer)
{
	if (CAST<CPlayer*>(pPlayer)->Get_FSM()->GetCurrentState() == CPlayerState_ROLL::Instance())
		return;
	if (CAST<CPlayer*>(pPlayer)->Get_Damaged())
		return;
	for (auto& pElement : *pBooms)
	{
		if (CheckSphereNRect(pElement->Get_Info(), pPlayer->Get_Rect()))
		{
			CAST<CPlayer*>(pPlayer)->Set_Damaged();
			pPlayer->Set_Hp(pPlayer->Get_Hp() - pElement->Get_Att());
			if (pPlayer->Get_Hp() <= 0)
				pPlayer->Set_Dead();
			return;
		}
	}
}

void CCOllisionMgr::Collision_Gun_Player(list<CObj*>* pGuns, CObj * pPlayer)
{
	if (pGuns->empty())
		return;
	if (pPlayer == nullptr)
		return;
	for (auto& iter = pGuns->begin(); iter != pGuns->end();)
	{
		if (CheckSphereNRect((*iter)->Get_Info(), pPlayer->Get_Rect()))
		{
			CAST<CPlayer*>(pPlayer)->Push_Gun((*iter));
			CAST<CGun*>(*iter)->Set_Subject(pPlayer);
			iter = pGuns->erase(iter);
			CSoundMgr::Get_Instance()->PlaySound(L"Item.wav", CSoundMgr::MAXCHANNEL);
		}
		else
			++iter;
	}
}

void CCOllisionMgr::Collision_Bullet_Monster(list<CObj*>* pBullets, list<CObj*>* pMonsters)
{
	for (auto& pBullet : *pBullets)
	{
		for (auto& pMonster : *pMonsters)
		{
			if (CheckSphereNRect(pBullet->Get_Info(), pMonster->Get_Rect()))
			{
				pMonster->Set_Hp(pMonster->Get_Hp() - pBullet->Get_Att());
				if (pMonster->Get_Hp() <= 0)
					pMonster->Set_Dead();
				pBullet->Set_Dead();
			}
		}
	}
}

void CCOllisionMgr::Collision_Razer_Monster(list<CObj*>* pRazers, list<CObj*>* pMonsters)
{
	for (auto& pBullet : *pRazers)
	{
		for (auto& pMonster : *pMonsters)
		{
			bool bCool = true;
			if (pMonster->Get_ID()== OBJ::NORMAL)
				bCool = CAST<CMonster*>(pMonster)->Get_RazerCool();
			else if (pMonster->Get_ID() == OBJ::RIFLE)
				bCool = CAST<CRifleMonster*>(pMonster)->Get_RazerCool();
			else if (pMonster->Get_ID() == OBJ::BIRD)
				bCool = CAST<CWizard*>(pMonster)->Get_RazerCool();
			else if (pMonster->Get_ID() == OBJ::WIZARD)
				bCool = CAST<CBird*>(pMonster)->Get_RazerCool();
			else if (pMonster->Get_ID() == OBJ::BOSS)
				bCool = CAST<CBoss*>(pMonster)->Get_RazerCool();
			if (bCool == true)
				continue;

			if (CheckSphereNRect(pBullet->Get_Info(), pMonster->Get_Rect()))
			{
				pMonster->Set_Hp(pMonster->Get_Hp() - pBullet->Get_Att());
				if (pMonster->Get_ID() == OBJ::NORMAL)
					CAST<CMonster*>(pMonster)->Set_RazerCool();
				else if (pMonster->Get_ID() == OBJ::RIFLE)
					CAST<CRifleMonster*>(pMonster)->Set_RazerCool();
				else if (pMonster->Get_ID() == OBJ::WIZARD)
					CAST<CWizard*>(pMonster)->Set_RazerCool();
				else if (pMonster->Get_ID() == OBJ::BIRD)
					CAST<CBird*>(pMonster)->Set_RazerCool();
				else if (pMonster->Get_ID() == OBJ::BOSS)
					CAST<CBoss*>(pMonster)->Set_RazerCool();
				
				if (pMonster->Get_Hp() <= 0)
					pMonster->Set_Dead();
				//cout << pMonster->Get_Hp() << endl;
				break;
			}
		}
	}
}

void CCOllisionMgr::Collision_Razer_Desk(list<CObj*>* pRazers, list<CObj*>* pDesks)
{
	for (auto& pDesk : *pDesks)
	{
		for (auto& iter = (*pRazers).begin(); iter != pRazers->end(); ++iter)
		{
			if (CAST<CDesk*>(pDesk)->Get_Check() && CheckSphereNRect((*iter)->Get_Info(), pDesk->Get_Rect()) &&
				CAST<CDesk*>(pDesk)->Get_RazerCool() == false)
			{
				pDesk->Set_Dead();
				break;
			}
		}
	}
}

void CCOllisionMgr::Collision_Dreadshot_Monster_Bullet(list<CObj*>* pDreadshots, list<CObj*>* pMonsters, list<CObj*>* pBullets)
{
	for (auto& pDreadshot : *pDreadshots)
	{
		for (auto& pMonster : *pMonsters)
		{
			if (CheckSphere(pDreadshot->Get_Info(), pMonster->Get_Info()))
			{
				if (pMonster->Get_ID() == OBJ::NORMAL)
				{
					CAST<CMonster*>(pMonster)->Get_FSM()->ChangeState(CMonsterState_STUN::Instance());
				}
				else if (pMonster->Get_ID() == OBJ::RIFLE)
				{
					CAST<CRifleMonster*>(pMonster)->Get_FSM()->ChangeState(CRifleMonsterState_STUN::Instance());
				}
				else if (pMonster->Get_ID() == OBJ::WIZARD)
				{
					CAST<CWizard*>(pMonster)->Get_FSM()->ChangeState(CWizardState_STUN::Instance());
				}
				else if (pMonster->Get_ID() == OBJ::BIRD)
				{
					if(CAST<CBird*>(pMonster)->Get_FSM()->GetCurrentState() != CBirdState_COOL::Instance())
						CAST<CBird*>(pMonster)->Get_FSM()->ChangeState(CBirdState_STUN::Instance());
				}
				else if (pMonster->Get_ID() == OBJ::BOSS)
				{
					CAST<CBoss*>(pMonster)->Get_FSM()->ChangeState(CBossState_STUN::Instance());
				}
			}
		}
		for (auto& pBullet : *pBullets)
		{
			if (CheckSphere(pDreadshot->Get_Info(), pBullet->Get_Info()))
			{
				pBullet->Set_Dead();
			}
		}
		pDreadshot->Set_Dead();
	}
}
void CCOllisionMgr::Collision_Desk_Bullet(list<CObj*>* pDesks, list<CObj*>* pBullets)
{
	if (pDesks->empty() || pBullets->empty())
		return;
	for (auto& pDesk : *pDesks)
	{
		if (!CAST<CDesk*>(pDesk)->Get_Check())
			continue;
		for (auto& pBullet : *pBullets)
		{
			if (CheckSphereNRect(pBullet->Get_Info(), pDesk->Get_Rect()))
			{
				pDesk->Set_Hp(pDesk->Get_Hp() - 1);
				if (pDesk->Get_Hp() <= 0)
					pDesk->Set_Dead();
				pBullet->Set_Dead();
			}
		}
	}
}
void CCOllisionMgr::Collision_Object_Desk(list<CObj*>* pObjs, list<CObj*>* pDesks)
{
	if (pDesks->empty() || pObjs->empty())
		return;
	RECT rc = {};
	for (auto& pDesk : *pDesks)
	{
		for (auto& pObj : *pObjs)
		{
			if (IntersectRect(&rc, pObj->Get_Rect(), pDesk->Get_Rect()))
			{
				float fX = SCAST<float>(rc.right - rc.left);
				float fY = SCAST<float>(rc.bottom - rc.top);
				
				
				if (pObj->Get_ID() == OBJ::ME && !CAST<CDesk*>(pDesk)->Get_Check() && CAST<CPlayer*>(pObj)->Get_FSM()->GetCurrentState() == CPlayerState_ROLL::Instance())
				{
					continue;
				}
				else
				{
					if (!CAST<CDesk*>(pDesk)->Get_Check() || pObj->Get_ID() != OBJ::ME)
					{
						if (fX > fY)
						{
							if (pObj->Get_Info()->fY < pDesk->Get_Info()->fY)
							{
								pObj->Move_Pos(0, -fY);
							}
							else
								pObj->Move_Pos(0, fY);
						}
						else
						{
							if (pObj->Get_Info()->fX < pDesk->Get_Info()->fX)
							{
								pObj->Move_Pos(-fX, 0);
							}
							else
								pObj->Move_Pos(fX, 0);
						}
					}
					else if (CAST<CDesk*>(pDesk)->Get_Check())
					{

						if (fX > fY)
						{
							if (pObj->Get_Info()->fY < pDesk->Get_Info()->fY)
							{
								pDesk->Move_Pos(0, fY / 2);
								pObj->Move_Pos(0, -fY / 2);
							}
							else
							{
								pDesk->Move_Pos(0, -fY / 2);
								pObj->Move_Pos(0, fY / 2);
							}
						}
						else
						{
							if (pObj->Get_Info()->fX < pDesk->Get_Info()->fX)
							{
								pDesk->Move_Pos(fX / 2, 0);
								pObj->Move_Pos(-fX / 2, 0);
							}
							else
							{
								pDesk->Move_Pos(-fX / 2, 0);
								pObj->Move_Pos(fX / 2, 0);
							}
						}
					}
				}
			}
		}
	}
}
void CCOllisionMgr::Collision_Object_Wall(list<CObj*>* pObjs, vector<CObj*>* pWalls)
{
	if (pObjs->empty() || pWalls->empty())
		return;
	for (auto* pObj : *pObjs)
	{
		int* p = CTileMgr::Get_Instance()->Get_CullSize(pObj->Get_Info(), 3);
		RECT rc = { p[0] * TILECX, p[1] * TILECY, p[2] * TILECX, p[3] * TILECY };
		POINT pt = { (LONG)(pObj->Get_Info()->fX), (LONG)(pObj->Get_Info()->fY) };
		if (!PtInRect(&rc, pt))
			continue;
		RECT temp = {};
		for (int i = p[1]; i < p[3]; ++i)
		{
			for (int j = p[0]; j < p[2]; ++j)
			{
				size_t iIndex = j + TILEX * i;
				if (0 > iIndex || iIndex > pWalls->size() || CAST<CTile*>((*pWalls)[iIndex])->Get_Option() == 0)
					continue;
				if (IntersectRect(&temp, pObj->Get_Rect(), (*pWalls)[iIndex]->Get_Rect()))
				{
					float fX = (float)(temp.right - temp.left);
					float fY = (float)(temp.bottom - temp.top);
					if (fX > fY)
					{
						if (pObj->Get_Info()->fY < (*pWalls)[iIndex]->Get_Info()->fY)
						{
							pObj->Move_Pos(0, -fY);
						}
						else
							pObj->Move_Pos(0, fY);
					}
					else
					{
						if (pObj->Get_Info()->fX < (*pWalls)[iIndex]->Get_Info()->fX)
						{
							pObj->Move_Pos(-fX, 0);
						}
						else
							pObj->Move_Pos(fX, 0);
					}
				}
			}
		}
	}

}
void CCOllisionMgr::Collision_Bullet_Wall(list<CObj*>* pObjs, vector<CObj*>* pWalls)
{

	for (auto* pObj : *pObjs)
	{
		int* p = CTileMgr::Get_Instance()->Get_CullSize(pObj->Get_Info(), 2);
		RECT temp = {};
		for (int i = p[1]; i < p[3]; ++i)
		{
			for (int j = p[0]; j < p[2]; ++j)
			{
				int iIndex = j + TILEX * i;
				if (0 > iIndex || iIndex > 8000 || CAST<CTile*>((*pWalls)[iIndex])->Get_Option() == 0)
					continue;
				if (IntersectRect(&temp, pObj->Get_Rect(), (*pWalls)[iIndex]->Get_Rect()))
				{
					pObj->Set_Dead();
				}
			}
		}
	}
}
void CCOllisionMgr::Collision_Shop_Player(CObj * pShop, CObj * pPlayer)
{
	RECT temp = {};
	if (IntersectRect(&temp, pShop->Get_Rect(), pPlayer->Get_Rect()))
	{
		float fX = (float)(temp.right - temp.left);
		float fY = (float)(temp.bottom - temp.top);
		if (fX > fY)
		{
			if (pPlayer->Get_Info()->fY < pShop->Get_Info()->fY)
			{
				pPlayer->Move_Pos(0, -fY);
			}
			else
				pPlayer->Move_Pos(0, fY);
		}
		else
		{
			if (pPlayer->Get_Info()->fX < pShop->Get_Info()->fX)
			{
				pPlayer->Move_Pos(-fX, 0);
			}
			else
				pPlayer->Move_Pos(fX, 0);
		}
	}
}
bool CCOllisionMgr::Collision_Shop_Bullet(RECT * pInfo, list<CObj*>* pBullets, list<CObj*>* pRazers)
{
	for (auto& pBullet : *pBullets)
	{
		POINT pt = { (LONG)(pBullet->Get_Info()->fX), (LONG)(pBullet->Get_Info()->fY) };
		if (PtInRect(pInfo, pt))
		{
			return true;
		}
	}
	for (auto& pRazer : *pRazers)
	{
		POINT pt = { (LONG)(pRazer->Get_Info()->fX), (LONG)(pRazer->Get_Info()->fY) };
		if (PtInRect(pInfo, pt))
		{
			return true;
		}
	}
	return false;
}
void CCOllisionMgr::Collision_Shop_Buy(CObj * pShop, CObj * pPlayer)
{
	RECT rt = { 960, 2100, 1980, 2900 };
	POINT pt = { (LONG)(pPlayer->Get_Info()->fX), (LONG)(pPlayer->Get_Info()->fY) };
	if (!PtInRect(&rt, pt))
		return;
	
	RECT*	pRt = CAST<CShop*>(pShop)->Get_CollisionRect();
	int*	pSell = CAST<CShop*>(pShop)->Get_iSell();
	int		iValue = CAST<CShop*>(pShop)->Get_iValue();

	RECT rc = {};
	for (int i = 0; i < 4; ++i)
	{
		if (IntersectRect(&rc, &pRt[i], pPlayer->Get_Rect()))
		{
			if (CKeyMgr::Get_Instance()->KeyDown('E'))
			{
				if (pPlayer->Get_Gold() >= pSell[i] * iValue)
				{
					pPlayer->Set_Gold(pPlayer->Get_Gold() - pSell[i] * iValue);
					CObj* pObj = NULL;
					switch (i)
					{
					case 0:
						pPlayer->Set_Hp(pPlayer->Get_Hp() + 1);
						CSoundMgr::Get_Instance()->PlaySoundW(L"Item.wav", CSoundMgr::MAXCHANNEL);
						break;
					case 1:
						CAST<CPlayer*>(pPlayer)->Set_Dreadshot(CAST<CPlayer*>(pPlayer)->Get_Dreadshot() + 1);
						CSoundMgr::Get_Instance()->PlaySoundW(L"Item.wav", CSoundMgr::MAXCHANNEL);
						break;
					case 2:
						pObj = CAbstractFactory<CChargegun>::CreateGun(nullptr, 20.f, 0, true);
						pObj->Set_Size(100, 100);
						pObj->Set_Pos(pPlayer->Get_Info()->fX, pPlayer->Get_Info()->fY);
						//pObj->Set_ID(OBJ::CHARGE);
						pObj->Set_Att(5);
						CAST<CGun*>(pObj)->Set_GunType(GUN::CHARGE);
						CAST<CGun*>(pObj)->Set_Speed(10.f);
						CAST<CGun*>(pObj)->Set_BulletState(1, 100);
						CAST<CGun*>(pObj)->Set_Time(1000, 0);
						CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::GUN);
						break;
					case 3:
						pObj = CAbstractFactory<CRazer>::CreateGun(nullptr, 20.f, 10, true);
						pObj->Set_Size(100, 100);
						pObj->Set_Pos(pPlayer->Get_Info()->fX, pPlayer->Get_Info()->fY);
						//pObj->Set_ID(OBJ::CHARGE);
						pObj->Set_Att(1);
						CAST<CGun*>(pObj)->Set_GunType(GUN::RAZER);
						CAST<CGun*>(pObj)->Set_Speed(10.f);
						CAST<CGun*>(pObj)->Set_BulletState(5, 100);
						CAST<CGun*>(pObj)->Set_Time(1000, 800);
						CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::GUN);
						break;
					default:
						break;
					}
				}
			}
		}
	}
}
bool CCOllisionMgr::Collision_Mouse_Teleport(CObj * pMouse, list<CObj*>* pTeleports, CObj* pPlayer)
{
	POINT pt = { (LONG)(pMouse->Get_Info()->fX), (LONG)(pMouse->Get_Info()->fY) };
	for (auto& iter : *pTeleports)
	{
		if (PtInRect(CAST<CTeleport*>(iter)->Get_CollisionRect(), pt) && CAST<CTeleport*>(iter)->Get_On())
		{
			//cout << iter->Get_Info()->fX << " " << iter->Get_Info()->fY << endl;
			if (CKeyMgr::Get_Instance()->KeyDown(VK_RBUTTON) )
			{
				pPlayer->Set_Pos(iter->Get_Info()->fX, iter->Get_Info()->fY);
				CScrollMgr::Initialize(WINCX / 2 - pPlayer->Get_Info()->fX, WINCY / 2 - pPlayer->Get_Info()->fY);
				return true;
			}
		}
	}
	return false;
}
void CCOllisionMgr::Collision_Player_BossStage(CObj * pPlayer)
{
	RECT rc = {};
	RECT boss = { 95 * TILECX, 48 * TILECY, 96 * TILECX, 50 * TILECY };
	if (IntersectRect(&rc, pPlayer->Get_Rect(), &boss))
	{
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_BOSS);
	}
}
//void CCOllisionMgr::CollisionRect(list<CObj*>& rlistDst, list<CObj*>& rlistSrc)
//{
//	RECT rc = {}; 
//
//	for (auto& rDestObj: rlistDst)
//	{
//		for (auto& rSrcObj : rlistSrc)
//		{
//			if (IntersectRect(&rc, rDestObj->Get_Rect(), rSrcObj->Get_Rect()))
//			{
//				rDestObj->Set_Dead();
//				rSrcObj->Set_Dead();
//			}
//		}
//	}
//}
//void CCOllisionMgr::CollisionSphere(list<CObj*>& rlistDst, list<CObj*>& rlistSrc)
//{
//	for (auto& rDestObj : rlistDst)
//	{
//		for (auto& rSrcObj : rlistSrc)
//		{
//			if (CheckSphere(rDestObj->Get_Info(), rSrcObj->Get_Info()))
//			{
//				rDestObj->Set_Dead();
//				rSrcObj->Set_Dead();
//			}
//		}
//	}
//}

bool CCOllisionMgr::CheckRazerWall(INFO * pRazer)
{
	vector<CObj*>* pWalls = CTileMgr::Get_Instance()->Get_Tile();
	if (pWalls->empty())
		return false;
	int* p = CTileMgr::Get_Instance()->Get_CullSize();
	/*p[0] -= 10;
	p[1] -= 10;
	p[2] += 10;
	p[3] += 10;
	if (p[0] < 0)
		p[0] = 0;
	if (p[1] < 0)
		p[1] = 0;
	if (p[2] > TILECX * TILEX)
		p[2] = TILECX * TILEX;
	if (p[3] > TILECY * TILEY)
		p[3] = TILECY * TILEY;*/

	RECT rc = { p[0] * TILECX, p[1] * TILECY, p[2] * TILECX, p[3] * TILECY };
	POINT pt = { (LONG)(pRazer->fX), (LONG)(pRazer->fY) };
	if (!PtInRect(&rc, pt))
		return false;
	for (int i = p[1]; i < p[3]; ++i)
	{
		for (int j = p[0]; j < p[2]; ++j)
		{
			size_t iIndex = j + i * TILEX;
			if (0 > iIndex || iIndex > pWalls->size() || CAST<CTile*>((*pWalls)[iIndex])->Get_Option() == 0)
				continue;
			if (CheckSphereNRect(pRazer, (*pWalls)[iIndex]->Get_Rect()))
				return true;
		}
	}
	return false;
}

bool CCOllisionMgr::CheckSphere(INFO * pDst, INFO * pSrc)
{
	float fx = pDst->fX - pSrc->fX; 
	float fy = pDst->fY - pSrc->fY; 
	float fDist = sqrtf(fx * fx + fy * fy);

	float fRadiusSum = float((pDst->iCX >> 1) + (pSrc->iCX >> 1));

	if (fRadiusSum > fDist)
		return true;

	return false; 
}

bool CCOllisionMgr::CheckSphereNRect(INFO * pInfo, RECT * pRect)
{
	if ((pRect->left <= pInfo->fX && pInfo->fX <= pRect->right) ||
		(pRect->top <= pInfo->fY && pInfo->fY <= pRect->bottom))
	{
		RECT rc = {
			pRect->left - pInfo->iCX / 2,
			pRect->top - pInfo->iCY / 2,
			pRect->right + pInfo->iCX / 2,
			pRect->bottom + pInfo->iCX / 2
		};

		if ((rc.left <= pInfo->fX && pInfo->fX <= rc.right) &&
			(rc.top <= pInfo->fY && pInfo->fY <= rc.bottom))
			return true;
	}
	else
	{
		float fX = pInfo->fX - pRect->left;
		float fY = pInfo->fY - pRect->bottom;
		float fDist = sqrtf(fX * fX + fY * fY);
		if (fDist < pInfo->iCX / 2)
			return true;

		fX = pInfo->fX - pRect->right;
		fY = pInfo->fY - pRect->bottom;
		fDist = sqrtf(fX * fX + fY * fY);
		if (fDist < pInfo->iCX / 2)
			return true;

		fX = pInfo->fX - pRect->right;
		fY = pInfo->fY - pRect->top;
		fDist = sqrtf(fX * fX + fY * fY);
		if (fDist < pInfo->iCX / 2)
			return true;

		fX = pInfo->fX - pRect->left;
		fY = pInfo->fY - pRect->top;
		fDist = sqrtf(fX * fX + fY * fY);
		if (fDist < pInfo->iCX / 2)
			return true;
	}
	return false;
}
