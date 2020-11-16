#include "stdafx.h"
#include "Ground.h"
#include "Door.h"
#include "Teleport.h"

#include "AbstractFactory.h"
#include "ObjMgr.h"

void CGround::Make_Door(int x, int y, DOOR::TYPE eType)
{
	CObj* pObj = CAbstractFactory<CDoor>::Create();
	CAST<CDoor*>(pObj)->Set_DoorType(eType);
	CAST<CDoor*>(pObj)->Set_DoorPos(x, y);
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::DOOR);
	m_lstDoor.emplace_back(pObj);
}

void CGround::Make_Tele(int x, int y)
{
	CObj* pObj = CAbstractFactory<CTeleport>::Create();
	CAST<CTeleport*>(pObj)->Set_TelePos(x, y);
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::TELEPORT);
	m_lstTele.emplace_back(pObj);
}

CGround::CGround()
{
}


CGround::~CGround()
{
}

void CGround::Initialize()
{
	m_bFlag = false;
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	m_plstMonster = CObjMgr::Get_Instance()->Get_Monster();
}

int CGround::Update()
{
	bool bCheck = false;
	POINT pt = { (LONG)(m_pPlayer->Get_Info()->fX), (LONG)(m_pPlayer->Get_Info()->fY) };
	if (PtInRect(&m_tRect, pt))
	{
		if (m_bFlag == false)
		{
			for (auto& pPair : m_lstPosType)
			{
				POS tPos = pPair.first;

				CEffectMgr::MakeEffectMonsterInit(L"MonsterInit", FRAME(0, 5, 0, 1, 150, 0), tPos.fX * TILECX, tPos.fY * TILECY, 70, 70, pPair.second);
			}
		}
		m_bFlag = true;
		for (auto& pElement : m_lstTele)
			CAST<CTeleport*>(pElement)->Set_On(true);
		for (auto& pElement : *m_plstMonster)
		{
			pt = { SCAST<LONG>(pElement->Get_Info()->fX), SCAST<LONG>(pElement->Get_Info()->fY) };
			if (PtInRect(&m_tRect, pt))
			{
				bCheck = true;
			}
		}
		if (bCheck)//플레이어 몬스터 둘다있음
		{
			for (auto& pDoor : m_lstDoor)
			{
				CAST<CDoor*>(pDoor)->Set_Close();
			}
		}
		else
		{
			for (auto& pDoor : m_lstDoor)
			{
				CAST<CDoor*>(pDoor)->Set_Open();
			}
		}
	}
	return OBJ_NOEVENT;
}

void CGround::LateUpdate()
{
}

void CGround::Render(HDC hDC)
{
//#ifdef _DEBUG
//	POS tPos = CScrollMgr::Get_MouseScroll();
//	Rectangle(hDC, m_tRect.left + tPos.fX, m_tRect.top + tPos.fY, 
//		m_tRect.right + tPos.fX, m_tRect.bottom + tPos.fY);
//#endif
}

void CGround::Release()
{
}
