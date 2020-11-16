#pragma once
#include "Obj.h"
#include "StateMachine.h"

class CPlayer :
	public CObj
{
private:
	CObj*			m_pMouse;
	vector<CObj*>	m_vecGun;
	DWORD			m_dwTime;
	float			m_fRollAngle;
	int				m_iGunCount;
	int				m_iGunNow;
	int				m_iShield;
	int				m_iDreadshot;
	bool			m_bRoll;
	bool			m_bDamaged;
	bool			m_bCheat;
	StateMachine<CPlayer>*	m_pState;
public:
	StateMachine<CPlayer>*	Get_FSM() { return this->m_pState; }
public:
	void			Set_Roll(float fAngle);
	inline void		Set_RollEnd() { m_bRoll = false; }
	inline void		Set_Damaged() { m_bDamaged = true; m_dwTime = GetTickCount(); }
	inline void		Set_Dreadshot(int iDreadshot) { m_iDreadshot = iDreadshot; }
	inline bool		Get_Damaged() { return m_bDamaged; }
	inline float	Get_RollAngle() { return m_fRollAngle; }
	inline bool		Get_Roll() { return m_bRoll; }
	inline int		Get_Shield() { return m_iShield; }
	inline int		Get_Dreadshot() { return m_iDreadshot; }
	inline CObj*	Get_GunNow() { return m_vecGun[m_iGunNow]; }
	inline void		Up_GunNowCount() { m_iGunNow += 1; if (m_iGunNow >= m_iGunCount) m_iGunNow = 0; }
	inline void		Down_GunNowCount() { m_iGunNow -= 1; if (m_iGunNow < 0) m_iGunNow = m_iGunCount - 1; }
	void			Push_Gun(CObj* pGun) { m_vecGun.emplace_back(pGun); ++m_iGunCount; cout << m_iGunCount << endl; }
public:
	CPlayer();
	virtual ~CPlayer();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	void	CreateDreadShot();
private:
	void	KeyDown();
	void	SetOffset();
};