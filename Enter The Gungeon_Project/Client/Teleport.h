#pragma once
#include "Obj.h"
class CTeleport
	: public CObj
{
private:
	int		m_iPosX;
	int		m_iPosY;
	bool	m_bOn;
	RECT	m_tCollisionRect;
public:
	void	Set_TelePos(int iPosX, int iPosY) {
		m_iPosX = iPosX; m_iPosY = iPosY;
		m_tInfo.fX = iPosX * TILECX + m_tInfo.iCX / 2.f;
		m_tInfo.fY = iPosY * TILECY + m_tInfo.iCY / 2.f;
	}
public:
	void	RenderMap(HDC hDC, int iC);
	void	Set_On(bool bOn) { m_bOn = bOn; }
	bool	Get_On() { return m_bOn; }
	RECT*	Get_CollisionRect() { return &m_tCollisionRect; }
public:
	CTeleport();
	virtual ~CTeleport();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

