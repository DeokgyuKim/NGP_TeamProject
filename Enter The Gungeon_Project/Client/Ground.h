#pragma once
#include "Obj.h"
class CGround :
	public CObj
{
private:
	bool			m_bFlag;
	CObj*			m_pPlayer;
	list<CObj*>*	m_plstMonster;
	list<CObj*>		m_lstDoor;
	list<CObj*>		m_lstTele;
	list<pair<POS, OBJ::TYPE>>		m_lstPosType;
public:
	void			Push_Pos(POS& tPos, OBJ::TYPE eType) { m_lstPosType.emplace_back(tPos, eType); }
	void			Set_Rect(int x1, int y1, int x2, int y2)
	{
		m_tRect.left = TILECX * x1;
		m_tRect.top = TILECY * y1;
		m_tRect.right = TILECX * x2;
		m_tRect.bottom = TILECY * y2;
	}
	void			Make_Door(int x, int y, DOOR::TYPE eType);
	void			Make_Tele(int x, int y);
public:
	CGround();
	virtual ~CGround();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

