#pragma once
#include "Gun.h"
class CChargegun :
	public CGun
{
public:
	int		m_iCharge;
	DWORD	m_dwChargeTime;
	CObj*	m_pBullet;
public:
	virtual void	CreateBullet();
	virtual void	KeyDown();
public:
	CChargegun();
	virtual ~CChargegun();
};

