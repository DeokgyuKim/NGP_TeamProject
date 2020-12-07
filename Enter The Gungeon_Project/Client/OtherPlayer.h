#pragma once
#include "Obj.h"
#include "StateMachine.h"

class COtherPlayer :
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
public:
	COtherPlayer();
	virtual ~COtherPlayer();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
public:
	void SetFrameKey(TCHAR* pFramekey) { wcscpy_s(m_pFrameKey, sizeof(pFramekey), pFramekey); }
	void SetFrameStart(int iStart) { m_tFrame.iFrameStart = iStart; }
	void SetFrameVertical(int iVertical) { m_tFrame.iFrameVetical = iVertical; }
};