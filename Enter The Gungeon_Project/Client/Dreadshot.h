#pragma once
#include "Obj.h"
class CDreadshot :
	public CObj
{
private:
	int iC;
public:
	CDreadshot();
	virtual ~CDreadshot();
public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

