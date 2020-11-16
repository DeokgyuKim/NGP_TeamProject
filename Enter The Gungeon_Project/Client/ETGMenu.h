#pragma once
#include "Scene.h"
class CETGMenu :
	public CScene
{
private:
	FRAME	m_tFrame;
private:
	void	FrameMove();
	void	Set_Frame(int iStart, int iEnd, int iVertical, DWORD dwSpeed);
public:
	CETGMenu();
	virtual ~CETGMenu();
public:
	// CScene을(를) 통해 상속됨
	virtual void Initiailize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

