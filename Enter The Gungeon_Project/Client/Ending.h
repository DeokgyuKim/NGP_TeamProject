#pragma once
#include "Scene.h"
class CEnding :
	public CScene
{
private:
	HWND	m_hVideo;
public:
	CEnding();
	virtual ~CEnding();
public:
	// CScene��(��) ���� ��ӵ�
	virtual void Initiailize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

