#pragma once
#include "Obj.h"
#include "StateMachine.h"
class CWizard :
	public CObj
{
	CObj*			m_pPlayer;
	float			m_fDist;
	float			m_fShotAngle;
	int				m_iCount;
	int				m_iShapeCount;
	list<CObj*>		m_lstBullet;
	StateMachine<CWizard>*	m_pState;
	bool			m_bRazerCool;
	DWORD			m_dwRazer;
	MONSTER::DIR	m_eDir;
public:
	MONSTER::DIR Get_Dir() { return m_eDir; }
	void	Set_Dir(MONSTER::DIR eDir) { m_eDir = eDir; }
	bool	Get_RazerCool() { return m_bRazerCool; }
	void	Set_RazerCool() { if (m_bRazerCool == false) { m_bRazerCool = true; m_dwRazer = GetTickCount(); } }

	StateMachine<CWizard>*	Get_FSM() { return m_pState; }
	CObj*					Get_Player() { return m_pPlayer; }
	void					CreateBullet(float fX, float fY);
	float					Get_Dist() { return m_fDist; }
	list<CObj*>*			Get_lstBulet() { return &m_lstBullet; }
	void					Plus_Count() { m_iCount = (m_iCount + 1) % 3; }
	int						Get_Count() { return m_iCount; }
	void					Plus_ShapeCount() { ++m_iShapeCount; }
	int						Get_ShapeCount() { return m_iShapeCount; }
	void					Set_ShapeCount() { m_iShapeCount = 0; }
	float					Get_ShotAngle() { return m_fShotAngle; }
	void					Set_ShotAngle(float fAngle) { m_fShotAngle = fAngle; }
public:
	CWizard();
	virtual ~CWizard();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

