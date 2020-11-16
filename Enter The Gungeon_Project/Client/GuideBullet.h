#pragma once
#include "Obj.h"
class CGuideBullet :
	public CObj
{
private:
	bool	m_bLockOn;
	DWORD	m_dwTime;
	DWORD	m_dwDead;
public:
	void Set_LockOn() { m_bLockOn = true; }
public:
	CGuideBullet();
	virtual ~CGuideBullet();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

