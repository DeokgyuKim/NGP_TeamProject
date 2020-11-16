#pragma once
#include "Obj.h"
#include "StateMachine.h"

class CGun :
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
	void		Set_Selling(bool bSell) { m_bSelling = bSell; }
	void		Set_Value(int iValue) { m_iValue = iValue; }
	GUN::TYPE	Get_GunType() { return m_eGunType; }
	void	Set_GunType(GUN::TYPE eType) { m_eGunType = eType; }
	void	Set_Edge(float fAngle);
	void	Set_Subject(CObj* pSubject) { 
		m_pSubject = pSubject;
		if (m_pSubject == nullptr) 
			m_bSubject = false; 
		else 
			m_bSubject = true; 
	}
	void	Set_Dist(float fDist) { m_fDist = fDist; }
	void	Set_Target(bool bIsPlayer);
	void	Set_Rebound(int iRebound = 1) { m_iRebound = iRebound; }
	void	Set_Time(int iReloadTime, int iRateoffireTime) { m_iTime[GUN::RELOAD] = iReloadTime; m_iTime[GUN::RATEOFFIRE] = iRateoffireTime; }
	void	Set_BulletState(int iClip, int iMax) { m_iBullet[BULLET::COUNT_MAX] = iClip; m_iBullet[BULLET::COUNT_NOW] = m_iBullet[BULLET::COUNT_MAX]; 
	m_iBullet[BULLET::COUNT_ALL_MAX] = iMax; m_iBullet[BULLET::COUNT_ALL_NOW] = m_iBullet[BULLET::COUNT_ALL_MAX];	}
	CObj*	Get_Subject() { return m_pSubject; }
	int*	Get_Time() { return m_iTime; }
	int*	Get_BulletState() { return m_iBullet; }
	bool	Get_Reload() { return m_bReload; }
	float	Get_ReloadTime() { return m_fReloadTime; }
	virtual void	CreateBullet();
	virtual void	KeyDown();
	void	Reload();
public:
	CGun();
	virtual ~CGun();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

