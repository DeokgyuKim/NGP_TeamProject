#pragma once
#include "State.h"
#include "Monster.h"
class CMonsterState
{
public:
	CMonsterState();
	~CMonsterState();
};

class CMonsterState_IDLE : public State<CMonster>
{
	CMonsterState_IDLE() {}
	CMonsterState_IDLE(const CMonsterState_IDLE& _rVal) {}
public:
	static	CMonsterState_IDLE* Instance();
	virtual void Enter(CMonster *) override;
	virtual void Execute(CMonster *) override;
	virtual void Exit(CMonster *) override;
};

class CMonsterState_FOLLOW : public State<CMonster>
{
	CMonsterState_FOLLOW() {}
	CMonsterState_FOLLOW(const CMonsterState_FOLLOW& _rVal) {}
public:
	static	CMonsterState_FOLLOW* Instance();
	virtual void Enter(CMonster *) override;
	virtual void Execute(CMonster *) override;
	virtual void Exit(CMonster *) override;
};

class CMonsterState_SHOT : public State<CMonster>
{
	CMonsterState_SHOT() {}
	CMonsterState_SHOT(const CMonsterState_SHOT& _rVal) {}
public:
	static	CMonsterState_SHOT* Instance();
	virtual void Enter(CMonster *) override;
	virtual void Execute(CMonster *) override;
	virtual void Exit(CMonster *) override;
};

class CMonsterState_STUN : public State<CMonster>
{
	DWORD	dwTime;
	CMonsterState_STUN() {}
	CMonsterState_STUN(const CMonsterState_STUN& _rVal) {}
public:
	static	CMonsterState_STUN* Instance();
	virtual void Enter(CMonster *) override;
	virtual void Execute(CMonster *) override;
	virtual void Exit(CMonster *) override;
};
