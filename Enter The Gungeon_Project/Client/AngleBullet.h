#pragma once
#include "Obj.h"
class CAngleBullet :
	public CObj
{
private:
	bool			m_bMove;
	//DWORD			m_dwTime;
	HDC				m_hMemDC;
	BULLET::TYPE	m_eType;
	DWORD			m_dwTime;
public:
	void	Set_Move(bool bMove) { m_bMove = bMove; }
	void	Set_Type(BULLET::TYPE eType) {
		m_eType = eType;
		if (m_eType == BULLET::CHARGE)
			m_hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"ChargeBullet");
		else if(m_eType == BULLET::RAZER)
			m_hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"RazerBullet");
		else if (m_eType == BULLET::NORMAL)
			m_hMemDC = CBmpMgr::Get_Instance()->Get_MemDC(L"NormalBullet");
	}
public:
	CAngleBullet();
	virtual ~CAngleBullet();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

