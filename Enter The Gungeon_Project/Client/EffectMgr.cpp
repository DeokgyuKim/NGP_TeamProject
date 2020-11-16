#include "stdafx.h"
#include "EffectMgr.h"
#include "Effect.h"
#include "MonsterInit.h"

#include "AbstractFactory.h"
#include "ObjMgr.h"

void CEffectMgr::MakeEffect(TCHAR * pKey, FRAME & tFrame, float fX, float fY, int iCX, int iCY, int iSize)
{
	CObj* pObj = CAbstractFactory<CEffect>::Create(fX, fY);
	pObj->Set_FrameKey(pKey);
	pObj->Set_Size(iCX, iCY);
	pObj->Set_Frame(tFrame.iFrameStart, tFrame.iFrameEnd, tFrame.iFrameVetical, tFrame.dwFrameSpeed);
	pObj->Set_Frame_Plus(true);
	CAST<CEffect*>(pObj)->Set_BigSize(iSize);
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::EFFECT);
	if(!lstrcmp(pKey, L"MonsterDie"))
		CSoundMgr::Get_Instance()->PlaySound(L"RedMonsterDie.mp3", CSoundMgr::MAXCHANNEL);

}

void CEffectMgr::MakeEffectMonsterInit(TCHAR * pKey, FRAME & tFrame, float fX, float fY, int iCX, int iCY, OBJ::TYPE eID, int iSize)
{
	CObj* pObj = CAbstractFactory<CMonsterInit>::Create(fX, fY);
	pObj->Set_ID(eID);
	pObj->Set_FrameKey(pKey);
	pObj->Set_Size(iCX, iCY);
	pObj->Set_Frame(tFrame.iFrameStart, tFrame.iFrameEnd, tFrame.iFrameVetical, tFrame.dwFrameSpeed);
	pObj->Set_Frame_Plus(true);
	CAST<CEffect*>(pObj)->Set_BigSize(iSize);
	CObjMgr::Get_Instance()->Push_Object(pObj, OBJ::EFFECT);
}

CEffectMgr::CEffectMgr()
{
}


CEffectMgr::~CEffectMgr()
{
}
