#pragma once
#include "Gun.h"


class CShotgun :
	public CGun
{
public:
	CShotgun();
	virtual ~CShotgun();
public:
	virtual void	CreateBullet();
};

