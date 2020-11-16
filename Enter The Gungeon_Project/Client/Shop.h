#pragma once
#include "Obj.h"
class CShop :
	public CObj
{
private:
	RECT	m_tCollisionRect[4];
	int		m_iSell[4];
	int		m_iValue;
	DWORD	m_dwValue;
	bool	m_bValue;
public:
	RECT*	Get_CollisionRect() { return m_tCollisionRect; }
	int*	Get_iSell() { return m_iSell; }
	int		Get_iValue() { return m_iValue; }
public:
	CShop();
	virtual ~CShop();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

