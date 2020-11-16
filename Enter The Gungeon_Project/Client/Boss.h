#pragma once
#include "Obj.h"
#include "StateMachine.h"
class CBoss :
	public CObj
{
private:
	CObj*			m_pPlayer;
	bool			m_bRazerCool;
	DWORD			m_dwRazer;
	DWORD			m_dwDead;
	RECT			m_tCollisionRect;
	int				m_iCount;
	StateMachine<CBoss>* m_pState;
public:
	virtual void Set_Dead();
	void	CreateAtt(float fX, float fY, float fAngle);
	void	CreateRadial(float fAngle);
	StateMachine<CBoss>* Get_FSM() { return m_pState; }
	int		Get_Count() { return m_iCount; }
	void	Set_Count(int iCount) { m_iCount = iCount; }
	bool	Get_RazerCool() { return m_bRazerCool; }
	void	Set_RazerCool() { if (m_bRazerCool == false) { m_bRazerCool = true; m_dwRazer = GetTickCount(); } }
	CObj*	Get_Player() { return m_pPlayer; }
	virtual RECT* Get_Rect() { return &m_tCollisionRect; }
public:
	CBoss();
	virtual ~CBoss();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

