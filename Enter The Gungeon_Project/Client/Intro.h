#pragma once
#include "Scene.h"
class CIntro :
	public CScene
{
private:
	HWND	m_hVideo;
public:
	CIntro();
	virtual ~CIntro();
public:
	// CScene��(��) ���� ��ӵ�
	virtual void Initiailize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

