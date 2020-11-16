#pragma once
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
	virtual void Set_Dead()
	{
		m_bDead = true;
	}
	bool Get_Dead() { return m_bDead; }
	void Set_Angle(float fAngle) { m_fAngle = fAngle; }
	void Set_Speed(float fSpeed) { m_fSpeed = fSpeed; }
	void Set_Size(int iCX, int iCY) { m_tInfo.iCX = iCX; m_tInfo.iCY = iCY; }
	void Set_Att(int iAtt) { m_iAtt = iAtt; }
	void Set_Hp(int iHp) { m_iHp = iHp; if (m_iHp < 0) m_iHp = 0; }
	void Set_ID(OBJ::TYPE eID) { m_eID = eID; }
	void Set_Gold(int iGold) { m_iGold = iGold; }
public:
	inline virtual RECT*	Get_Rect() { return &m_tRect; }
	inline INFO*			Get_Info() { return &m_tInfo; }
	inline float			Get_Angle() { return m_fAngle; }
	inline int				Get_Hp() { return m_iHp; }
	inline int				Get_Att() { return m_iAtt; }
	inline float			Get_Speed() { return m_fSpeed; }
	inline OBJ::TYPE		Get_ID() { return m_eID; }
	inline int				Get_Gold() { return m_iGold; }
	inline void				Move_Pos(float fX, float fY) { m_tInfo.fX += fX; m_tInfo.fY += fY; }
public:
	virtual void Initialize()		= 0; 
	virtual int	 Update()			= 0;
	virtual void LateUpdate()		= 0;
	virtual void Render(HDC hDC)	= 0;
	virtual void Release()			= 0;
public:
	void UpdateRect();
	void Set_Frame(int iStart, int iEnd, int iVertical, DWORD dwSpeed) {
		m_tFrame.iFrameStart = iStart;
		m_tFrame.iFrameEnd = iEnd;
		m_tFrame.iFrameVetical = iVertical;
		m_tFrame.dwFrameSpeed = dwSpeed;
		m_tFrame.dwFrameTime = GetTickCount();
	}
	void Set_Frame_Plus(bool bPlus) {
		if (bPlus)
			m_tFrame.iPlus = 1;
		else
			m_tFrame.iPlus = -1;
	}
	void Set_Frame_Plus_Zero() { m_tFrame.iPlus = 0; }
	void Set_Frame_Start_Init() { m_tFrame.iFrameStart = 0; }
	void Set_FrameKey(TCHAR* m_pKey) { m_pFrameKey = m_pKey; }
	void FrameMove();
protected:
	OBJ::TYPE	m_eID;
	INFO		m_tInfo;
	RECT		m_tRect;
	FRAME		m_tFrame;
	TCHAR*		m_pFrameKey;
	float		m_fSpeed; 
	bool		m_bDead; 
	float		m_fAngle;
	int			m_iHp;
	int			m_iAtt;
	int			m_iGold;
};

