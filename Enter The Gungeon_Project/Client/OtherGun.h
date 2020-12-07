#pragma once
#include "Obj.h"
#include "StateMachine.h"

class COtherGun :
	public CObj
{
protected:
	int				m_iValue;
	bool			m_bSelling;
	int				m_iRenderCount;
	GUN::TYPE		m_eGunType;
	CObj*			m_pSubject;
	CObj*			m_pTarget;
	POS				m_tEdge;
	DWORD			m_dwTime[GUN::END];
	float			m_fReloadTime;
	float			m_fDist;
	int				m_iTime[GUN::END];
	int				m_iBullet[BULLET::END];
	int				m_iRebound;
	bool			m_bReload;
	bool			m_bSubject;
public:
	void SetRenderCnt(int Cnt) { m_iRenderCount = Cnt; }
	int				m_iPlayerNum;
public:
	COtherGun();
	virtual ~COtherGun();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

