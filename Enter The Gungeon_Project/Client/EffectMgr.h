#pragma once

class CEffectMgr
{
public:
	static void MakeEffect(TCHAR* pKey, FRAME& tFrame, float fX, float fY, int iCX, int iCY, int iSize = 1);
	static void MakeEffectMonsterInit(TCHAR* pKey, FRAME& tFrame, float fX, float fY, int iCX, int iCY, OBJ::TYPE eID, int iSize = 1);
public:
	CEffectMgr();
	~CEffectMgr();
};

