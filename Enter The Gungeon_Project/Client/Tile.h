#pragma once
#include "Obj.h"
class CTile :
	public CObj
{
private:
	int		m_iDrawID;
	int		m_iOption;
public:
	CTile();
	virtual ~CTile();
public:
	int		Get_DrawID() { return m_iDrawID; }
	int		Get_Option() { return m_iOption; }
	void	Set_DrawID(int iDrawID) { m_iDrawID = iDrawID; }
	void	Set_Option(int iOption) { m_iOption = iOption; }
	void	Draw_GuideLine(HDC hDC);
	void	Render(HDC hDC, int iC);
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

