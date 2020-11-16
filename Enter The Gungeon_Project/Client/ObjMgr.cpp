#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "COllisionMgr.h"
#include "SceneMgr.h"
#include "Player.h"
#include "TileMgr.h"

CObjMgr* CObjMgr::m_pInstance = nullptr; 

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
}

void CObjMgr::Push_Object(CObj* pObj, OBJ::ID eID)
{
	m_lstObject[eID].emplace_back(pObj);
}

void CObjMgr::Clear_Object(OBJ::ID eID)
{
	if (m_lstObject[eID].empty())
		return;
	for (auto& pElement : m_lstObject[eID])
		delete pElement;
	m_lstObject[eID].clear();
}

void CObjMgr::Wheel_Up_N_Down(int zDelta)
{
	switch (zDelta)
	{
	case 120:
		CAST<CPlayer*>(m_lstObject[OBJ::PLAYER].front())->Up_GunNowCount();
		break;
	case -120:
		CAST<CPlayer*>(m_lstObject[OBJ::PLAYER].front())->Down_GunNowCount();
		break;
	default:
		break;
	}
}

CObj * CObjMgr::Get_Target(CObj * pSourceObj, OBJ::ID eID)
{
	if(m_lstObject[eID].empty())
		return nullptr;

	CObj* pCriteria = m_lstObject[eID].front();
	float x1 = pSourceObj->Get_Info()->fX - pCriteria->Get_Info()->fX; 
	float y1 = pSourceObj->Get_Info()->fY - pCriteria->Get_Info()->fY;
	float fdist1 = sqrtf(x1 * x1 + y1 * y1); 

	for (auto& rDstObj : m_lstObject[eID])
	{
		float x2 = pSourceObj->Get_Info()->fX - rDstObj->Get_Info()->fX;
		float y2 = pSourceObj->Get_Info()->fY - rDstObj->Get_Info()->fY;
		float fdist2 = sqrtf(x2 * x2 + y2 * y2);

		if (fdist2 < fdist1)
		{
			pCriteria = rDstObj;
			fdist1 = fdist2;
		}
	}
	return pCriteria; 
}

CObj * CObjMgr::Get_Boss()
{
	
	for (auto& pElement : m_lstObject[OBJ::MONSTER])
		if (pElement->Get_ID() == OBJ::BOSS)
			return pElement;
	return nullptr;
	
}

void CObjMgr::Update()
{
	for (int i = 0; i < OBJ::END; ++i)
	{
		if (i == OBJ::WALL)
			continue;
		for (auto& iter = m_lstObject[i].begin(); iter != m_lstObject[i].end(); )
		{
			int iEvent = (*iter)->Update();
			if (OBJ_DEAD == iEvent)
			{
				delete *iter;
				*iter = nullptr;
				iter = m_lstObject[i].erase(iter);
			}
			else if (OBJ_BOSSDEAD == iEvent)
			{
				CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_ENDING);
				return;
			}
			else
				++iter;
		}
	}
}

void CObjMgr::LateUpdate()
{
	//int iCount = 0;
	for (int i = 0; i < OBJ::END; ++i)
	{
		if (i == OBJ::WALL)
			continue;
		for (auto& iter : m_lstObject[i])
		{
			iter->LateUpdate();
			if (m_lstObject[i].empty())
				break;
			//++iCount;
		}
	}
	//cout << iCount << endl;
	CCOllisionMgr::Collision_Object_Wall(&m_lstObject[OBJ::PLAYER], CTileMgr::Get_Instance()->Get_Tile());
	CCOllisionMgr::Collision_Object_Wall(&m_lstObject[OBJ::MONSTER], CTileMgr::Get_Instance()->Get_Tile());
	CCOllisionMgr::Collision_Object_Wall(&m_lstObject[OBJ::DESK], CTileMgr::Get_Instance()->Get_Tile());
	CCOllisionMgr::Collision_Bullet_Wall(&m_lstObject[OBJ::M_BULLET], CTileMgr::Get_Instance()->Get_Tile());
	CCOllisionMgr::Collision_Bullet_Wall(&m_lstObject[OBJ::P_BULLET], CTileMgr::Get_Instance()->Get_Tile());
	CCOllisionMgr::Collision_Bullet_Monster(&m_lstObject[OBJ::P_BULLET], &m_lstObject[OBJ::MONSTER]);
	CCOllisionMgr::Collision_Razer_Monster(&m_lstObject[OBJ::RAZER], &m_lstObject[OBJ::MONSTER]);
	CCOllisionMgr::Collision_Razer_Desk(&m_lstObject[OBJ::RAZER], &m_lstObject[OBJ::DESK]);
	CCOllisionMgr::Collision_Bullet_Player(&m_lstObject[OBJ::M_BULLET], m_lstObject[OBJ::PLAYER].front());
	CCOllisionMgr::Collision_Boom_Player(&m_lstObject[OBJ::BOOM], m_lstObject[OBJ::PLAYER].front());
	CCOllisionMgr::Collision_Dreadshot_Monster_Bullet(&m_lstObject[OBJ::DREADSHOT], &m_lstObject[OBJ::MONSTER], &m_lstObject[OBJ::M_BULLET]);
	CCOllisionMgr::Collision_Gun_Player(&m_lstObject[OBJ::GUN], m_lstObject[OBJ::PLAYER].front());
	CCOllisionMgr::Collision_Desk_Bullet(&m_lstObject[OBJ::DESK], &m_lstObject[OBJ::M_BULLET]);
	CCOllisionMgr::Collision_Desk_Bullet(&m_lstObject[OBJ::DESK], &m_lstObject[OBJ::P_BULLET]);
	CCOllisionMgr::Collision_Object_Desk(&m_lstObject[OBJ::PLAYER], &m_lstObject[OBJ::DESK]);
	CCOllisionMgr::Collision_Object_Desk(&m_lstObject[OBJ::MONSTER], &m_lstObject[OBJ::DESK]);
	if (CSceneMgr::Get_Instance()->Get_SceneID() == CSceneMgr::SCENE_STAGE)
	{
		CCOllisionMgr::Collision_Shop_Player(m_lstObject[OBJ::SHOP].front(), m_lstObject[OBJ::PLAYER].front());
		CCOllisionMgr::Collision_Shop_Buy(m_lstObject[OBJ::SHOP].front(), m_lstObject[OBJ::PLAYER].front());
		CCOllisionMgr::Collision_Player_BossStage(m_lstObject[OBJ::PLAYER].front());
	}
}

void CObjMgr::Render(HDC hDC)
{
	for (int i = 0; i < OBJ::END; ++i)
	{
		if (i == OBJ::WALL)
			continue;
		for (auto& iter : m_lstObject[i])
			iter->Render(hDC);
	}
}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJ::END; ++i)
	{
		if (i == OBJ::WALL)
			continue;
		for (auto& iter : m_lstObject[i])
		{
			if (iter)
			{
				delete iter;
				iter = nullptr;
			}
		}
		m_lstObject[i].clear();
	}
}
