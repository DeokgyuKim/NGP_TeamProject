#pragma once

template <typename T>
class CAbstractFactory
{
public:
	static CObj* CreateGun(CObj* pSubject, float fDist, int iRebound, bool bIsPlayer)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		CAST<CGun*>(pObj)->Set_Subject(pSubject);
		CAST<CGun*>(pObj)->Set_Target(bIsPlayer);
		CAST<CGun*>(pObj)->Set_Dist(fDist);
		CAST<CGun*>(pObj)->Set_Rebound(iRebound);
		return pObj;
	}
	static CObj* Create()
	{
		CObj* pObj = new T; 
		pObj->Initialize(); 
		return pObj;
	}
	static CObj* Create(float x, float y)
	{
		CObj* pObj = new T;
		pObj->Initialize(); 
		pObj->Set_Pos(x, y);
		return pObj; 
	}
	static CObj* Create(float x, float y, float fAngle)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(x, y);
		pObj->Set_Angle(fAngle);
		return pObj;
	}
	static CObj* Create(float x, float y, float fAngle, float fSpeed, int iCX, int iCY)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(x, y);
		pObj->Set_Angle(fAngle);
		pObj->Set_Speed(fSpeed);
		pObj->Set_Size(iCX, iCY);
		return pObj;
	}
};
