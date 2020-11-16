#pragma once
#include "Obj.h"
class CBox :
	public CObj
{
private:
	int			m_iCount;
	GUN::TYPE	m_eType;
public:
	void	Set_BoxType(GUN::TYPE eType) { m_eType = eType; }
public:
	CBox();
	virtual ~CBox();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

