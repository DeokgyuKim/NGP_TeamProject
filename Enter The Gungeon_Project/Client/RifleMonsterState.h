#pragma once
#include "State.h"
#include "RifleMonster.h"

class CRifleMonsterState
{
public:
	CRifleMonsterState();
	~CRifleMonsterState();
};


class CRifleMonsterState_IDLE : public State<CRifleMonster>
{
	CRifleMonsterState_IDLE() {}
	CRifleMonsterState_IDLE(const CRifleMonsterState_IDLE& _rVal) {}
public:
	static	CRifleMonsterState_IDLE* Instance();
	virtual void Enter(CRifleMonster *) override;
	virtual void Execute(CRifleMonster *) override;
	virtual void Exit(CRifleMonster *) override;
};

class CRifleMonsterState_FOLLOW : public State<CRifleMonster>
{
	CRifleMonsterState_FOLLOW() {}
	CRifleMonsterState_FOLLOW(const CRifleMonsterState_FOLLOW& _rVal) {}
public:
	static	CRifleMonsterState_FOLLOW* Instance();
	virtual void Enter(CRifleMonster *) override;
	virtual void Execute(CRifleMonster *) override;
	virtual void Exit(CRifleMonster *) override;
};

class CRifleMonsterState_SHOT : public State<CRifleMonster>
{
	CRifleMonsterState_SHOT() {}
	CRifleMonsterState_SHOT(const CRifleMonsterState_SHOT& _rVal) {}
public:
	static	CRifleMonsterState_SHOT* Instance();
	virtual void Enter(CRifleMonster *) override;
	virtual void Execute(CRifleMonster *) override;
	virtual void Exit(CRifleMonster *) override;
};

class CRifleMonsterState_STUN : public State<CRifleMonster>
{
	DWORD	dwTime;
	CRifleMonsterState_STUN() {}
	CRifleMonsterState_STUN(const CRifleMonsterState_STUN& _rVal) {}
public:
	static	CRifleMonsterState_STUN* Instance();
	virtual void Enter(CRifleMonster *) override;
	virtual void Execute(CRifleMonster *) override;
	virtual void Exit(CRifleMonster *) override;
};


