#pragma once
#include "Obj.h"
class CDoor :
	public CObj
{
private:
	DOOR::TYPE		m_eType;
	bool			m_bOpen;
	int				m_iPosX;
	int				m_iPosY;
public:
	void		Set_Open();
	void		Set_Close();
	void		Set_DoorPos(int iPosX, int iPosY) { 
		m_iPosX = iPosX; m_iPosY = iPosY;
		m_tInfo.fX = iPosX * TILECX + m_tInfo.iCX / 2.f;
		m_tInfo.fY = iPosY * TILECY + m_tInfo.iCY / 2.f;
	}
	DOOR::TYPE	Get_DoorType() { return m_eType; }
	void		Set_DoorType(DOOR::TYPE eType) { 
		m_eType = eType; 
		switch (m_eType)
		{
		case DOOR::LEFT:
			m_pFrameKey = L"LeftDoor1";
			m_tInfo.iCX = 64;
			m_tInfo.iCY = 128;
			break;
		case DOOR::RIGHT:
			m_pFrameKey = L"RightDoor1";
			m_tInfo.iCX = 64;
			m_tInfo.iCY = 128;
			break;
		case DOOR::TOP:
			m_pFrameKey = L"UpDoor1";
			m_tInfo.iCX = 128;
			m_tInfo.iCY = 64;
			break;
		case DOOR::BOTTOM:
			m_pFrameKey = L"DownDoor1";
			m_tInfo.iCX = 128;
			m_tInfo.iCY = 64;
			break;
		default:
			break;
		}
	}
public:
	CDoor();
	virtual ~CDoor();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

