#pragma once
#include "Scene.h"
class CETGBoss :
	public CScene
{
private:
	DWORD	m_dwIntro;
	bool	m_bIntro;
	FRAME	m_tFrame;
public:
	CETGBoss();
	virtual ~CETGBoss();
public:
	// CScene��(��) ���� ��ӵ�
	virtual void Initiailize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

