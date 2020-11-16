#pragma once
#include "Obj.h"
#include "StateMachine.h"
class CRifleMonster :
	public CObj
{
private:
	CObj*			m_pPlayer;
	CObj*			m_pGun;
	bool			m_bShot;
	bool			m_bRazerCool;
	DWORD			m_dwRazer;
	MONSTER::DIR	m_eDir;
	StateMachine<CRifleMonster>*	m_pState;
public:
	bool	Get_RazerCool() { return m_bRazerCool; }
	void	Set_RazerCool() { if (m_bRazerCool == false) { m_bRazerCool = true; m_dwRazer = GetTickCount(); } }
	void	Set_Dir(MONSTER::DIR eDir) { m_eDir = eDir; }
	MONSTER::DIR Get_Dir() { return m_eDir; }

	StateMachine<CRifleMonster>*	Get_FSM() { return m_pState; }
public:
	CObj*	Get_Player() { return m_pPlayer; }
	CObj*	Get_Gun() { return m_pGun; }
public:
	CRifleMonster();
	virtual ~CRifleMonster();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

