#include "stdafx.h"
#include "BirdState.h"


CBirdState::CBirdState()
{
}


CBirdState::~CBirdState()
{
}

CBirdState_IDLE * CBirdState_IDLE::Instance()
{
	static CBirdState_IDLE Instance;
	return &Instance;
}

void CBirdState_IDLE::Enter(CBird * owner)
{
	owner->Set_Frame(0, 3, 0, 200);
}

void CBirdState_IDLE::Execute(CBird * owner)
{
	float fX = owner->Get_Player()->Get_Info()->fX - owner->Get_Info()->fX;
	float fY = owner->Get_Player()->Get_Info()->fY - owner->Get_Info()->fY;
	float fDist = sqrtf(fX * fX + fY * fY);

	//ShotState
	if (fDist < 100)
	{
		owner->Get_FSM()->ChangeState(CBirdState_SHOT::Instance());
	}
	//FollowState
	else if (fDist < FOLLOW)
	{
		owner->Get_FSM()->ChangeState(CBirdState_FOLLOW::Instance());
	}
}

void CBirdState_IDLE::Exit(CBird * owner)
{
}

CBirdState_FOLLOW * CBirdState_FOLLOW::Instance()
{
	static CBirdState_FOLLOW Instance;
	return &Instance;
}

void CBirdState_FOLLOW::Enter(CBird * owner)
{
}

void CBirdState_FOLLOW::Execute(CBird * owner)
{
	owner->Move_Pos(cosf(DEGREETORADIAN(owner->Get_Angle())) * owner->Get_Speed(),
		-sinf(DEGREETORADIAN(owner->Get_Angle())) * owner->Get_Speed());

	float fX = owner->Get_Player()->Get_Info()->fX - owner->Get_Info()->fX;
	float fY = owner->Get_Player()->Get_Info()->fY - owner->Get_Info()->fY;
	float fDist = sqrtf(fX * fX + fY * fY);

	//ShotState
	if (fDist < 100)
	{
		owner->Get_FSM()->ChangeState(CBirdState_SHOT::Instance());
	}
	//IDLEState
	else if (fDist >= FOLLOW)
	{
		owner->Get_FSM()->ChangeState(CBirdState_IDLE::Instance());
	}
	owner->FrameMove();
}

void CBirdState_FOLLOW::Exit(CBird * owner)
{
}

CBirdState_SHOT * CBirdState_SHOT::Instance()
{
	static CBirdState_SHOT Instance;
	return &Instance;
}

void CBirdState_SHOT::Enter(CBird * owner)
{
	m_dwTime = GetTickCount();
	owner->Set_Frame(0, 11, 1, 40);
}

void CBirdState_SHOT::Execute(CBird * owner)
{
	if (m_dwTime + 500 < GetTickCount())
	{
		owner->Get_FSM()->ChangeState(CBirdState_COOL::Instance());
	}
	////if (CAST<CGun*>(owner->Get_Gun())->Get_FSM()->GetCurrentState() != CGunState_RELOAD::Instance())
	////	CAST<CGun*>(owner->Get_Gun())->Get_FSM()->ChangeState(CGunState_RELOAD::Instance());
	//float fX = owner->Get_Player()->Get_Info()->fX - owner->Get_Info()->fX;
	//float fY = owner->Get_Player()->Get_Info()->fY - owner->Get_Info()->fY;
	//float fDist = sqrtf(fX * fX + fY * fY);

	////ShotState
	//if (fDist >= 800)
	//{
	//	owner->Get_FSM()->ChangeState(CBirdState_IDLE::Instance());
	//}
	////FollowState
	//else if (fDist < 800 && fDist >= 400)
	//{
	//	owner->Get_FSM()->ChangeState(CBirdState_FOLLOW::Instance());
	//}
	owner->FrameMove();
}

void CBirdState_SHOT::Exit(CBird * owner)
{
	/*owner->CreateBullet(owner->Get_Info()->fX - 80 + 10 * (owner->Get_ShapeCount() - 16),
		owner->Get_Info()->fY + 80 - 20 * (owner->Get_ShapeCount() - 16));*/
	owner->Plus_ShapeCount();
	m_dwTime = GetTickCount();
}

CBirdState_STUN * CBirdState_STUN::Instance()
{
	static CBirdState_STUN Instance;
	return &Instance;
}

void CBirdState_STUN::Enter(CBird * owner)
{
	dwTime = GetTickCount();
}

void CBirdState_STUN::Execute(CBird * owner)
{
	if (dwTime + 2000 < GetTickCount())
	{
		owner->Get_FSM()->ChangeState(CBirdState_IDLE::Instance());
		dwTime = GetTickCount();
	}
}

void CBirdState_STUN::Exit(CBird * owner)
{
}

CBirdState_COOL * CBirdState_COOL::Instance()
{
	static CBirdState_COOL Instance;
	return &Instance;
}

void CBirdState_COOL::Enter(CBird * owner)
{
	dwTime = GetTickCount();
	owner->Set_Dead();
	CSoundMgr::Get_Instance()->PlaySound(L"ShotGun.mp3", CSoundMgr::MAXCHANNEL);
	owner->CreateBullet();
}

void CBirdState_COOL::Execute(CBird * owner)
{
	if (dwTime + 1000 < GetTickCount())
	{
		owner->Get_FSM()->ChangeState(CBirdState_IDLE::Instance());
		dwTime = GetTickCount();
	}
}

void CBirdState_COOL::Exit(CBird * owner)
{
}
