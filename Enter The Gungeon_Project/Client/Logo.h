#pragma once
#include "Scene.h"
class CLogo :
	public CScene
{
private:
	DWORD	m_dwTime;
public:
	CLogo();
	virtual ~CLogo();
public:
	// CScene��(��) ���� ��ӵ�
	virtual void Initiailize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

