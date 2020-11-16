#pragma once
#include "Gun.h"
class CRazer :
	public CGun
{
public:
	virtual void	CreateBullet();
public:
	CRazer();
	virtual ~CRazer();
};

