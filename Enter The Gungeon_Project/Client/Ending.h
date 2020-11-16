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
	// CScene을(를) 통해 상속됨
	virtual void Initiailize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

