#pragma once
#include "State.h"
#include "Wizard.h"
class CWizardState
{
public:
	CWizardState();
	~CWizardState();
};

class CWizardState_IDLE : public State<CWizard>
{
	CWizardState_IDLE() {}
	CWizardState_IDLE(const CWizardState_IDLE& _rVal) {}
public:
	static	CWizardState_IDLE* Instance();
	virtual void Enter(CWizard *owner) override;
	virtual void Execute(CWizard *owner) override;
	virtual void Exit(CWizard *owner) override;
};

class CWizardState_FOLLOW : public State<CWizard>
{
	CWizardState_FOLLOW() {}
	CWizardState_FOLLOW(const CWizardState_FOLLOW& _rVal) {}
public:
	static	CWizardState_FOLLOW* Instance();
	virtual void Enter(CWizard *owner) override;
	virtual void Execute(CWizard *owner) override;
	virtual void Exit(CWizard *owner) override;
};

class CWizardState_SHOT : public State<CWizard>
{
	DWORD		m_dwTime;
	CWizardState_SHOT() {}
	CWizardState_SHOT(const CWizardState_SHOT& _rVal) {}
public:
	static	CWizardState_SHOT* Instance();
	virtual void Enter(CWizard *owner) override;
	virtual void Execute(CWizard *owner) override;
	virtual void Exit(CWizard *owner) override;
};

class CWizardState_STUN : public State<CWizard>
{
	DWORD dwTime;
	CWizardState_STUN() {}
	CWizardState_STUN(const CWizardState_STUN& _rVal) {}
public:
	static	CWizardState_STUN* Instance();
	virtual void Enter(CWizard *owner) override;
	virtual void Execute(CWizard *owner) override;
	virtual void Exit(CWizard *owner) override;
};

class CWizardState_COOL : public State<CWizard>
{
	DWORD dwTime;
	CWizardState_COOL() {}
	CWizardState_COOL(const CWizardState_COOL& _rVal) {}
public:
	static	CWizardState_COOL* Instance();
	virtual void Enter(CWizard *owner) override;
	virtual void Execute(CWizard *owner) override;
	virtual void Exit(CWizard *owner) override;
};

