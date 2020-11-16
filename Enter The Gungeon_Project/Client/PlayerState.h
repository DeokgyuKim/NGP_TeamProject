#pragma once
#include "State.h"
#include "Player.h"
class CPlayerState
{
public:
	CPlayerState();
	~CPlayerState();
};

class CPlayerState_IDLE : public State<CPlayer>
{
	CPlayerState_IDLE() {}
	CPlayerState_IDLE(const CPlayerState_IDLE& _rVal) {}
public:
	static CPlayerState_IDLE* Instance();
	virtual void Enter(CPlayer* owner);
	virtual void Execute(CPlayer* owner);
	virtual void Exit(CPlayer* owner);
};

class CPlayerState_RUN : public State<CPlayer>
{
	DWORD dwTime;
	CPlayerState_RUN() {}
	CPlayerState_RUN(const CPlayerState_RUN& _rVal) {}
public:
	static CPlayerState_RUN* Instance();
	virtual void Enter(CPlayer* owner);
	virtual void Execute(CPlayer* owner);
	virtual void Exit(CPlayer* owner);
};

class CPlayerState_ROLL : public State<CPlayer>
{
	CPlayerState_ROLL() {}
	CPlayerState_ROLL(const CPlayerState_ROLL& _rVal) {}
public:
	static CPlayerState_ROLL* Instance();
	virtual void Enter(CPlayer* owner);
	virtual void Execute(CPlayer* owner);
	virtual void Exit(CPlayer* owner);
};
