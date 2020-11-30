#pragma once
#include <Windows.h>
#include "struct.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();
public:
	void Set_Pos(float fx, float fy)
	{
		m_tInfo.fX = fx; 
		m_tInfo.fY = fy;
	}
public:
	inline virtual RECT*	Get_Rect() { return &m_tRect; }
	inline INFO*			Get_Info() { return &m_tInfo; }
	inline float			Get_Angle() { return m_fAngle; }
	inline int				Get_Hp() { return m_iHp; }
	inline int				Get_Att() { return m_iAtt; }
	inline float			Get_Speed() { return m_fSpeed; }
	inline int				Get_Gold() { return m_iGold; }
	inline void				Move_Pos(float fX, float fY) { /*m_tInfo.fX += fX; m_tInfo.fY += fY; */}
	inline TCHAR*			Get_FrameKey() { return m_pFrameKey; }
public:
	virtual void Initialize()		= 0; 
	virtual int	 Update()			= 0;
	virtual void LateUpdate()		= 0;
	virtual void Render(HDC hDC)	= 0;
	virtual void Release()			= 0;
public:
	void UpdateRect();
protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	TCHAR*		m_pFrameKey;
	float		m_fSpeed; 
	bool		m_bDead; 
	float		m_fAngle;
	int			m_iHp;
	int			m_iAtt;
	int			m_iGold;
};

