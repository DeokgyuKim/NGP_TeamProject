#pragma once
#include "Scene.h"
class CETGStage :
	public CScene
{
	bool	m_bMapOn;
public:
	CETGStage();
	virtual ~CETGStage();
public:
	// CScene��(��) ���� ��ӵ�
	virtual void Initiailize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

