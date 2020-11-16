#include "stdafx.h"
#include "MonsterInit.h"

#include "RifleMonster.h"
#include "Wizard.h"
#include "Bird.h"
#include "Monster.h"

#include "SceneMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"

CMonsterInit::CMonsterInit()
{
}


CMonsterInit::~CMonsterInit()
{
	Release();
}

void CMonsterInit::Release()
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() != CSceneMgr::SCENE_STAGE)
		return;
	CObj* pObj = NULL;
	switch (m_eID)
	{
	case OBJ::NORMAL:
		pObj = CAbstractFactory<CMonster>::Create(m_tInfo.fX, m_tInfo.fY);
		CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::MONSTER);
		break;
	case OBJ::RIFLE:
		pObj = CAbstractFactory<CRifleMonster>::Create(m_tInfo.fX, m_tInfo.fY);
		CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::MONSTER);
		break;
	case OBJ::WIZARD:
		pObj = CAbstractFactory<CWizard>::Create(m_tInfo.fX, m_tInfo.fY);
		CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::MONSTER);
		break;
	case OBJ::BIRD:
		pObj = CAbstractFactory<CBird>::Create(m_tInfo.fX, m_tInfo.fY);
		CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::MONSTER);
		break;
	default:
		break;
	}
}
