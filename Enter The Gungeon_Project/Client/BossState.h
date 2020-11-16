#pragma once
#include "State.h"
#include "Boss.h"

class CBossState
{
public:
	CBossState();
	~CBossState();
};

class CBossState_IDLE : public State<CBoss>
{
	int		iCount;
	DWORD	dwTime;
	CBossState_IDLE() { iCount = 0; }
	CBossState_IDLE(const CBossState_IDLE& rVal) {}
public:
	static CBossState_IDLE* Instance();
	virtual void Enter(CBoss *owner) override;
	virtual void Execute(CBoss *owner) override;
	virtual void Exit(CBoss *owner) override;

};

class CBossState_ATT1 : public State<CBoss>
{
	DWORD	dwTime;
	int		iCount;
	CBossState_ATT1();
	CBossState_ATT1(const CBossState_ATT1& rVal) {}
public:
	static CBossState_ATT1* Instance();
	virtual void Enter(CBoss *owner) override;
	virtual void Execute(CBoss *owner) override;
	virtual void Exit(CBoss *owner) override;
};
class CBossState_ATT2 : public State<CBoss>
{
	DWORD	dwTime;
	int		iCount;
	CBossState_ATT2();
	CBossState_ATT2(const CBossState_ATT2& rVal) {}
public:
	static CBossState_ATT2* Instance();
	virtual void Enter(CBoss *owner) override;
	virtual void Execute(CBoss *owner) override;
	virtual void Exit(CBoss *owner) override;
};

class CBossState_ATT3 : public State<CBoss>
{
	DWORD	dwTime;
	int 	iCount;
	CBossState_ATT3();
	CBossState_ATT3(const CBossState_ATT3& rVal) {}
public:
	static CBossState_ATT3* Instance();
	virtual void Enter(CBoss *owner) override;
	virtual void Execute(CBoss *owner) override;
	virtual void Exit(CBoss *owner) override;
};

class CBossState_ATT4 : public State<CBoss>
{
	DWORD	dwTime;
	int 	iCount;
	float	fAngle;
	CBossState_ATT4();
	CBossState_ATT4(const CBossState_ATT4& rVal) {}
public:
	static CBossState_ATT4* Instance();
	virtual void Enter(CBoss *owner) override;
	virtual void Execute(CBoss *owner) override;
	virtual void Exit(CBoss *owner) override;
};

class CBossState_STUN : public State<CBoss>
{
	DWORD dwTime;
	CBossState_STUN();
	CBossState_STUN(const CBossState_STUN& rVal) {}
public:
	static CBossState_STUN* Instance();
	virtual void Enter(CBoss *owner) override;
	virtual void Execute(CBoss *owner) override;
	virtual void Exit(CBoss *owner) override;
};