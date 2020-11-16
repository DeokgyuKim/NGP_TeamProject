#pragma once
#include "Obj.h"
class CRazerbullet :
	public CObj
{
private:
	bool			m_bCheck;
	HDC				m_hMemDC;
	BULLET::TYPE	m_eType;
	DWORD			m_dwTime;
public:
	CRazerbullet();
	virtual ~CRazerbullet();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

