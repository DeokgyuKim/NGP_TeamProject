#pragma once
#include "Obj.h"
#include "StateMachine.h"
class CMonster :
	public CObj
{
private:
	CObj*			m_pPlayer;
	CObj*			m_pGun;
	StateMachine<CMonster>*		m_pState;
	bool			m_bRazerCool;
	DWORD			m_dwRazer;
	MONSTER::DIR	m_eDir;
public:
	StateMachine<CMonster>*		Get_FSM() { return m_pState; }
public:
	bool	Get_RazerCool() { return m_bRazerCool; }
	void	Set_RazerCool() { if (m_bRazerCool == false) { m_bRazerCool = true; m_dwRazer = GetTickCount(); } }
	CObj*	Get_Player() { return m_pPlayer; }
	CObj*	Get_Gun() { return m_pGun; }
public:
	CMonster();
	virtual ~CMonster();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

