#include "stdafx.h"
#include "MonsterState.h"
#include "Gun.h"
//#include "Gunstate.h"

CMonsterState::CMonsterState()
{
}


CMonsterState::~CMonsterState()
{
}

CMonsterState_IDLE * CMonsterState_IDLE::Instance()
{
	static CMonsterState_IDLE Instance;
	return &Instance;
}

void CMonsterState_IDLE::Enter(CMonster *owner)
{
	owner->Set_Frame(0, 5, 0, 200);
}

void CMonsterState_IDLE::Execute(CMonster *owner)
{
	float fX = owner->Get_Player()->Get_Info()->fX - owner->Get_Info()->fX;
	float fY = owner->Get_Player()->Get_Info()->fY - owner->Get_Info()->fY;
	float fDist = sqrtf(fX * fX + fY * fY);

	//ShotState
	if (fDist < SHOT)
	{
		owner->Get_FSM()->ChangeState(CMonsterState_SHOT::Instance());
	}
	//FollowState
	else if (fDist < FOLLOW)
	{
		owner->Get_FSM()->ChangeState(CMonsterState_FOLLOW::Instance());
	}
}

void CMonsterState_IDLE::Exit(CMonster *owner)
{
}

CMonsterState_FOLLOW * CMonsterState_FOLLOW::Instance()
{
	static CMonsterState_FOLLOW Instance;
	return &Instance;
}

void CMonsterState_FOLLOW::Enter(CMonster *owner)
{
}

void CMonsterState_FOLLOW::Execute(CMonster *owner)
{
	owner->Move_Pos(cosf(DEGREETORADIAN(owner->Get_Angle())) * owner->Get_Speed(),
		-sinf(DEGREETORADIAN(owner->Get_Angle())) * owner->Get_Speed());

	float fX = owner->Get_Player()->Get_Info()->fX - owner->Get_Info()->fX;
	float fY = owner->Get_Player()->Get_Info()->fY - owner->Get_Info()->fY;
	float fDist = sqrtf(fX * fX + fY * fY);

	//ShotState
	if (fDist < SHOT)
	{
		owner->Get_FSM()->ChangeState(CMonsterState_SHOT::Instance());
	}
	//IDLEState
	else if (fDist >= FOLLOW)
	{
		owner->Get_FSM()->ChangeState(CMonsterState_IDLE::Instance());
	}
	owner->FrameMove();
}

void CMonsterState_FOLLOW::Exit(CMonster *owner)
{
}

CMonsterState_SHOT * CMonsterState_SHOT::Instance()
{
	static CMonsterState_SHOT Instance;
	return &Instance;
}

void CMonsterState_SHOT::Enter(CMonster *owner)
{
	owner->Set_Frame_Start_Init();
}

void CMonsterState_SHOT::Execute(CMonster *owner)
{
	CAST<CGun*>(owner->Get_Gun())->CreateBullet();
	//if (CAST<CGun*>(owner->Get_Gun())->Get_FSM()->GetCurrentState() != CGunState_RELOAD::Instance())
	//	CAST<CGun*>(owner->Get_Gun())->Get_FSM()->ChangeState(CGunState_RELOAD::Instance());
	float fX = owner->Get_Player()->Get_Info()->fX - owner->Get_Info()->fX;
	float fY = owner->Get_Player()->Get_Info()->fY - owner->Get_Info()->fY;
	float fDist = sqrtf(fX * fX + fY * fY);

	//ShotState
	if (fDist >= FOLLOW)
	{
		owner->Get_FSM()->ChangeState(CMonsterState_IDLE::Instance());
	}
	//FollowState
	else if (fDist < FOLLOW && fDist >= SHOT)
	{
		owner->Get_FSM()->ChangeState(CMonsterState_FOLLOW::Instance());
	}
	//owner->FrameMove();
}

void CMonsterState_SHOT::Exit(CMonster *owner)
{
}

CMonsterState_STUN * CMonsterState_STUN::Instance()
{
	static CMonsterState_STUN Instance;
	return &Instance;
}

void CMonsterState_STUN::Enter(CMonster *owner)
{
	dwTime = GetTickCount();
}

void CMonsterState_STUN::Execute(CMonster *owner)
{
	if (dwTime + 2000 < GetTickCount())
	{
		owner->Get_FSM()->ChangeState(CMonsterState_IDLE::Instance());
		dwTime = GetTickCount();
	}
}

void CMonsterState_STUN::Exit(CMonster *owner)
{
}
