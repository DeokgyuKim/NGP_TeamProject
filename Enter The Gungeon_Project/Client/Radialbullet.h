#pragma once
#include "Obj.h"
class CRadialbullet :
	public CObj
{
private:
	BULLET::TYPE	m_eType;
	DWORD			m_dwTime;
	bool			m_bRockOn;
public:
	inline void		Set_RockOn(){ m_bRockOn = true; }
public:
	CRadialbullet();
	virtual ~CRadialbullet();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

