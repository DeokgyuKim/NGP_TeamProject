#pragma once
#include "Obj.h"
class CBullet :
	public CObj
{
private:
	BULLET::TYPE m_eType;
public:
	CBullet();
	CBullet(float fx, float fy);
	virtual ~CBullet();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

