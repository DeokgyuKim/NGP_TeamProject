#pragma once
#include "Bird.h"
class CBirdState
{
public:
	CBirdState();
	~CBirdState();
};

class CBirdState_IDLE : public State<CBird>
{
	CBirdState_IDLE() {}
	CBirdState_IDLE(const CBirdState_IDLE& _rVal) {}
public:
	static	CBirdState_IDLE* Instance();
	virtual void Enter(CBird *owner) override;
	virtual void Execute(CBird *owner) override;
	virtual void Exit(CBird *owner) override;
};

class CBirdState_FOLLOW : public State<CBird>
{
	CBirdState_FOLLOW() {}
	CBirdState_FOLLOW(const CBirdState_FOLLOW& _rVal) {}
public:
	static	CBirdState_FOLLOW* Instance();
	virtual void Enter(CBird *owner) override;
	virtual void Execute(CBird *owner) override;
	virtual void Exit(CBird *owner) override;
};

class CBirdState_SHOT : public State<CBird>
{
	DWORD		m_dwTime;
	CBirdState_SHOT() {}
	CBirdState_SHOT(const CBirdState_SHOT& _rVal) {}
public:
	static	CBirdState_SHOT* Instance();
	virtual void Enter(CBird *owner) override;
	virtual void Execute(CBird *owner) override;
	virtual void Exit(CBird *owner) override;
};

class CBirdState_STUN : public State<CBird>
{
	DWORD dwTime;
	CBirdState_STUN() {}
	CBirdState_STUN(const CBirdState_STUN& _rVal) {}
public:
	static	CBirdState_STUN* Instance();
	virtual void Enter(CBird *owner) override;
	virtual void Execute(CBird *owner) override;
	virtual void Exit(CBird *owner) override;
};

class CBirdState_COOL : public State<CBird>
{
	DWORD dwTime;
	CBirdState_COOL() {}
	CBirdState_COOL(const CBirdState_COOL& _rVal) {}
public:
	static	CBirdState_COOL* Instance();
	virtual void Enter(CBird *owner) override;
	virtual void Execute(CBird *owner) override;
	virtual void Exit(CBird *owner) override;
};