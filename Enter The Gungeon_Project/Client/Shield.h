#pragma once
#include "Obj.h"
class CShield :
	public CObj
{
public:
	CShield();
	virtual ~CShield();

public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

