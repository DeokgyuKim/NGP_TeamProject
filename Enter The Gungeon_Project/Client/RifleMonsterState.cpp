#include "stdafx.h"
#include "RifleMonsterState.h"
#include "Gun.h"
//#include "Gunstate.h"

CRifleMonsterState::CRifleMonsterState()
{
}


CRifleMonsterState::~CRifleMonsterState()
{
}

CRifleMonsterState_IDLE * CRifleMonsterState_IDLE::Instance()
{
	static CRifleMonsterState_IDLE Instance;
	return &Instance;
}

void CRifleMonsterState_IDLE::Enter(CRifleMonster *owner)
{
	owner->Set_Frame(0, 5, 0, 200);
}

void CRifleMonsterState_IDLE::Execute(CRifleMonster *owner)
{
	float fX = owner->Get_Player()->Get_Info()->fX - owner->Get_Info()->fX;
	float fY = owner->Get_Player()->Get_Info()->fY - owner->Get_Info()->fY;
	float fDist = sqrtf(fX * fX + fY * fY);
	if (fDist < SHOT)
	{
		owner->Get_FSM()->ChangeState(CRifleMonsterState_SHOT::Instance());
	}
	else if (fDist < FOLLOW)
	{
		owner->Get_FSM()->ChangeState(CRifleMonsterState_FOLLOW::Instance());
	}
	owner->Get_Gun()->Update();
}

void CRifleMonsterState_IDLE::Exit(CRifleMonster *owner)
{
}

CRifleMonsterState_FOLLOW * CRifleMonsterState_FOLLOW::Instance()
{
	static CRifleMonsterState_FOLLOW Instance;
	return &Instance;
}

void CRifleMonsterState_FOLLOW::Enter(CRifleMonster *owner)
{
}

void CRifleMonsterState_FOLLOW::Execute(CRifleMonster *owner)
{
	float fX = owner->Get_Player()->Get_Info()->fX - owner->Get_Info()->fX;
	float fY = owner->Get_Player()->Get_Info()->fY - owner->Get_Info()->fY;
	float fDist = sqrtf(fX * fX + fY * fY);

	float fAngle = acosf(fX / fDist);
	owner->Set_Angle(RADIANTODEGREE(fAngle));
	if (owner->Get_Info()->fY < owner->Get_Player()->Get_Info()->fY)
		owner->Set_Angle(360.f - owner->Get_Angle());
	owner->Get_Gun()->Update();

	owner->Move_Pos(cosf(DEGREETORADIAN(owner->Get_Angle())) * owner->Get_Speed(), -sinf(DEGREETORADIAN(owner->Get_Angle())) * owner->Get_Speed());
	
	if (45 < owner->Get_Angle() && owner->Get_Angle() <= 135)
	{
		if (owner->Get_Dir() != MONSTER::UP)
		{
			owner->Set_Frame(0, 5, 1, 200);
			owner->Set_Dir(MONSTER::UP);
		}
	}
	else if (135 < owner->Get_Angle() && owner->Get_Angle() <= 225)
	{
		if (owner->Get_Dir() != MONSTER::LEFT)
		{
			owner->Set_Frame(0, 5, 2, 200);
			owner->Set_Dir(MONSTER::LEFT);
		}
	}
	else if (225 < owner->Get_Angle() && owner->Get_Angle() <= 315)
	{
		if (owner->Get_Dir() != MONSTER::DOWN)
		{
			owner->Set_Frame(0, 5, 3, 200);
			owner->Set_Dir(MONSTER::DOWN);
		}
	}
	else
	{
		if (owner->Get_Dir() != MONSTER::RIGHT)
		{
			owner->Set_Frame(0, 5, 0, 200);
			owner->Set_Dir(MONSTER::RIGHT);
		}
	}
	
	if (fDist < SHOT)
	{
		owner->Get_FSM()->ChangeState(CRifleMonsterState_SHOT::Instance());
	}
	else if (fDist >= FOLLOW)
	{
		owner->Get_FSM()->ChangeState(CRifleMonsterState_IDLE::Instance());
	}
	owner->FrameMove();
}

void CRifleMonsterState_FOLLOW::Exit(CRifleMonster *owner)
{
}

CRifleMonsterState_SHOT * CRifleMonsterState_SHOT::Instance()
{
	static CRifleMonsterState_SHOT Instance;
	return &Instance;
}

void CRifleMonsterState_SHOT::Enter(CRifleMonster *owner)
{
	float fX = owner->Get_Player()->Get_Info()->fX - owner->Get_Gun()->Get_Info()->fX;
	float fY = owner->Get_Player()->Get_Info()->fY - owner->Get_Gun()->Get_Info()->fY;
	float fDist = sqrtf(fX * fX + fY * fY);

	float fAngle = acosf(fX / fDist);
	owner->Set_Angle(RADIANTODEGREE(fAngle));
	if (owner->Get_Gun()->Get_Info()->fY < owner->Get_Player()->Get_Info()->fY)
		owner->Set_Angle(360.f - owner->Get_Angle());
	owner->Set_Angle(owner->Get_Angle() - 30.f);
	owner->Set_Frame_Start_Init();
}

void CRifleMonsterState_SHOT::Execute(CRifleMonster *owner)
{
	if (CAST<CGun*>(owner->Get_Gun())->Get_BulletState()[BULLET::COUNT_NOW] <= 0)
	{
		CAST<CGun*>(owner->Get_Gun())->Reload();
		//if(CAST<CGun*>(owner->Get_Gun())->Get_FSM()->GetCurrentState() != CGunState_RELOAD::Instance())
		//	CAST<CGun*>(owner->Get_Gun())->Get_FSM()->ChangeState(CGunState_RELOAD::Instance());
		owner->Get_FSM()->ChangeState(CRifleMonsterState_IDLE::Instance());
	}
	else
	{
		owner->Set_Angle(owner->Get_Angle() + (60.f / 65.f));
		owner->Get_Gun()->Set_Angle(owner->Get_Angle());
		CAST<CGun*>(owner->Get_Gun())->Set_Edge(owner->Get_Angle());
		CAST<CGun*>(owner->Get_Gun())->CreateBullet();
	}
}

void CRifleMonsterState_SHOT::Exit(CRifleMonster *owner)
{
}

CRifleMonsterState_STUN * CRifleMonsterState_STUN::Instance()
{
	static CRifleMonsterState_STUN Instance;
	return &Instance;
}

void CRifleMonsterState_STUN::Enter(CRifleMonster *owner)
{
	dwTime = GetTickCount();
}

void CRifleMonsterState_STUN::Execute(CRifleMonster *owner)
{
	if (dwTime + 2000 < GetTickCount())
	{
		owner->Get_FSM()->ChangeState(CRifleMonsterState_IDLE::Instance());
		dwTime = GetTickCount();
	}
}

void CRifleMonsterState_STUN::Exit(CRifleMonster *owner)
{
}
