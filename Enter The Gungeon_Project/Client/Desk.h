#pragma once
#include "Obj.h"
class CDesk :
	public CObj
{
public:
	enum DIR { LEFT, RIGHT, TOP, BOTTOM, END };
private:
	CObj*		m_pPlayer;
	RECT		m_tRectCollision[DIR::END];
	RECT		m_tCollisionRect;
	DIR			m_eCurDir;
	DIR			m_eDir;
	bool		m_bCheck;
	bool		m_bRazerCool;
	DWORD		m_dwRazer;
public:
	void			UpdateCollisionRect();
	DIR				Get_eDir() { return m_eDir; }
	bool			Get_Check() { return m_bCheck; }
	virtual RECT*	Get_Rect() {return &m_tCollisionRect;}
	bool			Get_RazerCool() { return m_bRazerCool; }
	void			Set_RazerCool() { if (m_bRazerCool == false) { m_bRazerCool = true; m_dwRazer = GetTickCount(); } }
private:
	void		ChangeState();
	void		UpdateDrawRect();
public:
	CDesk();
	virtual ~CDesk();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

