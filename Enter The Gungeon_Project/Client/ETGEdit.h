#pragma once
#include "Scene.h"
class CETGEdit :
	public CScene
{
private:
	bool	m_bGuideLine;
	DWORD	m_dwTime;
public:
	CETGEdit();
	virtual ~CETGEdit();
public:
	// CScene��(��) ���� ��ӵ�
	virtual void Initiailize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

