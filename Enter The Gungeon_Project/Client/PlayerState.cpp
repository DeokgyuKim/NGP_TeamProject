#include "stdafx.h"
#include "PlayerState.h"
#include "KeyMgr.h"
#include "Gun.h"

#include "NetWork.h"

CPlayerState::CPlayerState()
{
}


CPlayerState::~CPlayerState()
{
}

CPlayerState_IDLE * CPlayerState_IDLE::Instance()
{
	static CPlayerState_IDLE Instance;
	return &Instance;
}

void CPlayerState_IDLE::Enter(CPlayer * owner)
{
	owner->Set_Frame(0, 3, 0, 100);
}

void CPlayerState_IDLE::Execute(CPlayer * owner)
{
	if (CKeyMgr::Get_Instance()->KeyPressing('W'))
	{
		owner->Get_FSM()->ChangeState(CPlayerState_RUN::Instance());
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('A'))
	{
		owner->Get_FSM()->ChangeState(CPlayerState_RUN::Instance());
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('S'))
	{
		owner->Get_FSM()->ChangeState(CPlayerState_RUN::Instance());
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('D'))
	{
		owner->Get_FSM()->ChangeState(CPlayerState_RUN::Instance());
	}
	CAST<CGun*>(owner->Get_GunNow())->KeyDown();
	if (CKeyMgr::Get_Instance()->KeyDown('R'))
	{
		CAST<CGun*>(owner->Get_GunNow())->Reload();
	}
	if (CKeyMgr::Get_Instance()->KeyDown('Q'))
	{
		owner->CreateDreadShot();
	}
}

void CPlayerState_IDLE::Exit(CPlayer * owner)
{
}

CPlayerState_RUN * CPlayerState_RUN::Instance()
{
	static CPlayerState_RUN Instance;
	return &Instance;
}

void CPlayerState_RUN::Enter(CPlayer * owner)
{
	dwTime = 0;
	owner->Set_Frame(0, 7, 2, 100);
}

void CPlayerState_RUN::Execute(CPlayer * owner)
{
	if (dwTime + 300 < GetTickCount())
	{
		CEffectMgr::MakeEffect(L"PlayerWalkingEffect", FRAME{ 0, 7, 0, 1, 30, 0 }, owner->Get_Info()->fX, (float)(owner->Get_Rect()->bottom), 21, 21);
		CSoundMgr::Get_Instance()->PlaySound(L"Walk.mp3", CSoundMgr::MAXCHANNEL);
		dwTime = GetTickCount();
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('W'))
	{
		if (CKeyMgr::Get_Instance()->KeyPressing('A'))
		{
			owner->Move_Pos(-owner->Get_Speed() / sqrtf(2.f), -owner->Get_Speed() / sqrtf(2.f));
			if (fabs(owner->Get_Angle() - 135.f) >= 90)
				owner->Set_Frame_Plus(false);
			else
				owner->Set_Frame_Plus(true);
			if (CKeyMgr::Get_Instance()->KeyDown(VK_RBUTTON))
			{
				owner->Set_Roll(135.f);
				owner->Get_FSM()->ChangeState(CPlayerState_ROLL::Instance());
				CNetwork::GetInstance()->SetInputKey(KEY_RBUTTON);
			}
		}
		else if (CKeyMgr::Get_Instance()->KeyPressing('D'))
		{
			owner->Move_Pos(owner->Get_Speed() / sqrtf(2.f), -owner->Get_Speed() / sqrtf(2.f));
			if (fabs(owner->Get_Angle() - 45.f) >= 90)
				owner->Set_Frame_Plus(false);
			else
				owner->Set_Frame_Plus(true);
			if (CKeyMgr::Get_Instance()->KeyDown(VK_RBUTTON))
			{
				owner->Set_Roll(45.f);
				owner->Get_FSM()->ChangeState(CPlayerState_ROLL::Instance());
				CNetwork::GetInstance()->SetInputKey(KEY_RBUTTON);
			}
		}
		else
		{
			owner->Move_Pos(0, -owner->Get_Speed());
			if (fabs(owner->Get_Angle() - 90.f) >= 90)
				owner->Set_Frame_Plus(false);
			else
				owner->Set_Frame_Plus(true);
			if (CKeyMgr::Get_Instance()->KeyDown(VK_RBUTTON))
			{
				owner->Set_Roll(90.f);
				owner->Get_FSM()->ChangeState(CPlayerState_ROLL::Instance());
				CNetwork::GetInstance()->SetInputKey(KEY_RBUTTON);
			}
		}
	}
	else if (CKeyMgr::Get_Instance()->KeyPressing('S'))
	{
		if (CKeyMgr::Get_Instance()->KeyPressing('A'))
		{
			owner->Move_Pos(-owner->Get_Speed() / sqrtf(2.f), owner->Get_Speed() / sqrtf(2.f));
			if (fabs(owner->Get_Angle() - 225.f) >= 90)
				owner->Set_Frame_Plus(false);
			else
				owner->Set_Frame_Plus(true);
			if (CKeyMgr::Get_Instance()->KeyDown(VK_RBUTTON))
			{
				owner->Set_Roll(225.f);
				owner->Get_FSM()->ChangeState(CPlayerState_ROLL::Instance());
				CNetwork::GetInstance()->SetInputKey(KEY_RBUTTON);
			}
		}
		else if (CKeyMgr::Get_Instance()->KeyPressing('D'))
		{
			owner->Move_Pos(owner->Get_Speed() / sqrtf(2.f), owner->Get_Speed() / sqrtf(2.f));
			if (fabs(owner->Get_Angle() - 315.f) >= 90)
				owner->Set_Frame_Plus(false);
			else
				owner->Set_Frame_Plus(true);
			if (CKeyMgr::Get_Instance()->KeyDown(VK_RBUTTON))
			{
				owner->Set_Roll(315.f);
				owner->Get_FSM()->ChangeState(CPlayerState_ROLL::Instance());
				CNetwork::GetInstance()->SetInputKey(KEY_RBUTTON);
			}
		}
		else
		{
			owner->Move_Pos(0, owner->Get_Speed());
			if (fabs(owner->Get_Angle() - 270.f) >= 90)
				owner->Set_Frame_Plus(false);
			else
				owner->Set_Frame_Plus(true);
			if (CKeyMgr::Get_Instance()->KeyDown(VK_RBUTTON))
			{
				owner->Set_Roll(270.f);
				owner->Get_FSM()->ChangeState(CPlayerState_ROLL::Instance());
				CNetwork::GetInstance()->SetInputKey(KEY_RBUTTON);
			}
		}
	}
	else if (CKeyMgr::Get_Instance()->KeyPressing('D'))
	{
		owner->Move_Pos(owner->Get_Speed(), 0);
		if (fabs(owner->Get_Angle() - 0.f) >= 90)
			owner->Set_Frame_Plus(false);
		else
			owner->Set_Frame_Plus(true);
		if (CKeyMgr::Get_Instance()->KeyDown(VK_RBUTTON))
		{
			owner->Set_Roll(0.f);
			owner->Get_FSM()->ChangeState(CPlayerState_ROLL::Instance());
			CNetwork::GetInstance()->SetInputKey(KEY_RBUTTON);
		}
	}
	else if (CKeyMgr::Get_Instance()->KeyPressing('A'))
	{
		owner->Move_Pos(-owner->Get_Speed(), 0);
		if (fabs(owner->Get_Angle() - 180.f) >= 90)
			owner->Set_Frame_Plus(false);
		else
			owner->Set_Frame_Plus(true);
		if (CKeyMgr::Get_Instance()->KeyDown(VK_RBUTTON))
		{
			owner->Set_Roll(180.f);
			owner->Get_FSM()->ChangeState(CPlayerState_ROLL::Instance());
			CNetwork::GetInstance()->SetInputKey(KEY_RBUTTON);
		}
	}
	else
	{
		owner->Get_FSM()->ChangeState(CPlayerState_IDLE::Instance());
	}
	CAST<CGun*>(owner->Get_GunNow())->KeyDown();
	if (CKeyMgr::Get_Instance()->KeyDown('R'))
	{
		CAST<CGun*>(owner->Get_GunNow())->Reload();
	}
	if (CKeyMgr::Get_Instance()->KeyDown('Q'))
	{
		owner->CreateDreadShot();
	}
}

void CPlayerState_RUN::Exit(CPlayer * owner)
{
	owner->Set_Frame_Plus(true);
}

CPlayerState_ROLL * CPlayerState_ROLL::Instance()
{
	static CPlayerState_ROLL Instance;
	return &Instance;
}

void CPlayerState_ROLL::Enter(CPlayer * owner)
{
	owner->Set_Frame(0, 6, 1, 20);
	CEffectMgr::MakeEffect(L"PlayerJumpingEffect", FRAME{ 0, 3, 0, 1, 150, 0 }, owner->Get_Info()->fX, owner->Get_Info()->fY + 20, 36, 28);
}

void CPlayerState_ROLL::Execute(CPlayer * owner)
{
	owner->Move_Pos(cosf(DEGREETORADIAN(owner->Get_RollAngle())) * owner->Get_Speed(), -sinf(DEGREETORADIAN(owner->Get_RollAngle())) * owner->Get_Speed());
	owner->Set_Speed(owner->Get_Speed() - 1.f);
	if (owner->Get_Speed() <= PLAYER_SPEED)
	{
		owner->Set_Speed(PLAYER_SPEED);
		owner->Get_FSM()->ChangeState(CPlayerState_IDLE::Instance());
	}
	if (CKeyMgr::Get_Instance()->KeyDown('R'))
	{
		CAST<CGun*>(owner->Get_GunNow())->Reload();
	}
	if (CKeyMgr::Get_Instance()->KeyDown('Q'))
	{
		owner->CreateDreadShot();
	}
}

void CPlayerState_ROLL::Exit(CPlayer * owner)
{
	owner->Set_RollEnd();
}