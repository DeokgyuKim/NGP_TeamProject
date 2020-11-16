#pragma once
#include "Obj.h"
class CScrewBullet :
	public CObj
{
public:
	CScrewBullet();
	virtual ~CScrewBullet();
public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	POINT m_tCenter;
	float m_fRotAngle; // ���� ���� 
	float m_fRotDist; // ���� �Ÿ� 
	float m_fRotSpeed; // ���� ���ǵ� 
	// ���� ������ �ִ� ���ǵ�� ������ ������ �ʴ� ������ ���� ���ư��� ������ �ɰ�. 

	bool m_bIsInit; 
};

