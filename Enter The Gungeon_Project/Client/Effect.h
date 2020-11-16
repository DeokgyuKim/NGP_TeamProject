#pragma once
#include "Obj.h"
class CEffect :
	public CObj
{
private:
	BOOL	m_bFinish;
	int		m_iSize;
public:
	void	Set_BigSize(int iSize) { m_iSize = iSize; }
	CEffect();
	virtual ~CEffect();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

