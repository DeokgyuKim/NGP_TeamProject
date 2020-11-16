#pragma once
#include "Obj.h"
class CScrewBullet :
	public CObj
{
public:
	CScrewBullet();
	virtual ~CScrewBullet();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	POINT m_tCenter;
	float m_fRotAngle; // 공전 각도 
	float m_fRotDist; // 공전 거리 
	float m_fRotSpeed; // 공전 스피드 
	// 현재 가지고 있는 스피드와 각도는 보이지 않는 임의의 축이 나아가는 방향이 될것. 

	bool m_bIsInit; 
};

