#include "stdafx.h"
#include "BossState.h"


CBossState::CBossState()
{
}


CBossState::~CBossState()
{
}

CBossState_IDLE * CBossState_IDLE::Instance()
{
	static CBossState_IDLE Instance;
	return &Instance;
}

void CBossState_IDLE::Enter(CBoss * owner)
{
	owner->Set_FrameKey(L"Boss_Wait");
	owner->Set_Size(78, 140);
	owner->Set_Frame(0, 5, 0, 150);
	dwTime = GetTickCount();
}

void CBossState_IDLE::Execute(CBoss * owner)
{
	if (!owner->Get_Dead())
	{
		if (dwTime + 5000 < GetTickCount())
		{
			switch (iCount)
			{
			case 0:
				owner->Get_FSM()->ChangeState(CBossState_ATT1::Instance());
				break;
			case 1:
				owner->Get_FSM()->ChangeState(CBossState_ATT2::Instance());
				break;
			case 2:
				owner->Get_FSM()->ChangeState(CBossState_ATT3::Instance());
				break;
			case 3:
				owner->Get_FSM()->ChangeState(CBossState_ATT4::Instance());
				break;
			default:
				break;
			}
		}
	}
	owner->FrameMove();
}

void CBossState_IDLE::Exit(CBoss * owner)
{
	iCount = (iCount + 1) % 4;
}


CBossState_ATT1::CBossState_ATT1()
{
}

CBossState_ATT1 * CBossState_ATT1::Instance()
{
	static CBossState_ATT1 Instance;
	return &Instance;
}

void CBossState_ATT1::Enter(CBoss * owner)
{
	owner->Set_FrameKey(L"Boss_Attack_Left");
	owner->Set_Size(140, 158);
	owner->Set_Frame(0, 6, 0, 100);
	dwTime = GetTickCount();
	iCount = 0;
}

void CBossState_ATT1::Execute(CBoss * owner)
{
	if (dwTime + 100 < GetTickCount())
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Ump.wav", CSoundMgr::MAXCHANNEL);
		float fX = owner->Get_Player()->Get_Info()->fX - (owner->Get_Info()->fX - 100);
		float fY = owner->Get_Player()->Get_Info()->fY - owner->Get_Info()->fY;
		float fDist = sqrtf(fX * fX + fY * fY);

		float fAngle = acosf(fX / fDist);
		fAngle = (RADIANTODEGREE(fAngle));
		if (owner->Get_Info()->fY < owner->Get_Player()->Get_Info()->fY)
			fAngle = 360 - fAngle;

		owner->CreateAtt(owner->Get_Info()->fX - 100, owner->Get_Info()->fY, fAngle - 10.f);
		owner->CreateAtt(owner->Get_Info()->fX - 100, owner->Get_Info()->fY, fAngle);
		owner->CreateAtt(owner->Get_Info()->fX - 100, owner->Get_Info()->fY, fAngle + 10.f);
		dwTime = GetTickCount();
		if (++iCount == 7)
			owner->Get_FSM()->ChangeState(CBossState_IDLE::Instance());
	}
	owner->FrameMove();
}

void CBossState_ATT1::Exit(CBoss * owner)
{
}

CBossState_ATT2::CBossState_ATT2()
{
}

CBossState_ATT2 * CBossState_ATT2::Instance()
{
	static CBossState_ATT2 Instance;
	return &Instance;
}

void CBossState_ATT2::Enter(CBoss * owner)
{
	owner->Set_FrameKey(L"Boss_Attack_Right");
	owner->Set_Size(140, 158);
	owner->Set_Frame(0, 6, 0, 100);
	dwTime = GetTickCount();
	iCount = 0;
}

void CBossState_ATT2::Execute(CBoss * owner)
{
	if (dwTime + 100 < GetTickCount())
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Ump.wav", CSoundMgr::MAXCHANNEL);
		float fX = owner->Get_Player()->Get_Info()->fX - (owner->Get_Info()->fX + 100);
		float fY = owner->Get_Player()->Get_Info()->fY - owner->Get_Info()->fY;
		float fDist = sqrtf(fX * fX + fY * fY);

		float fAngle = acosf(fX / fDist);
		fAngle = (RADIANTODEGREE(fAngle));
		if (owner->Get_Info()->fY < owner->Get_Player()->Get_Info()->fY)
			fAngle = 360 - fAngle;
		owner->CreateAtt(owner->Get_Info()->fX + 100, owner->Get_Info()->fY, fAngle - 10.f);
		owner->CreateAtt(owner->Get_Info()->fX + 100, owner->Get_Info()->fY, fAngle);
		owner->CreateAtt(owner->Get_Info()->fX + 100, owner->Get_Info()->fY, fAngle + 10.f);
		dwTime = GetTickCount();
		if (++iCount == 7)
			owner->Get_FSM()->ChangeState(CBossState_IDLE::Instance());
	}
	owner->FrameMove();
}

void CBossState_ATT2::Exit(CBoss * owner)
{
}

CBossState_ATT3::CBossState_ATT3()
{
}

CBossState_ATT3 * CBossState_ATT3::Instance()
{
	static CBossState_ATT3 Instance;
	return &Instance;
}

void CBossState_ATT3::Enter(CBoss * owner)
{
	owner->Set_FrameKey(L"Boss_Ulti1_Standby");
	owner->Set_Size(110, 158);
	owner->Set_Frame(0, 10, 0, 150);
	dwTime = GetTickCount();
	iCount = 0;
}

void CBossState_ATT3::Execute(CBoss * owner)
{
	if (dwTime + 400 < GetTickCount())
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Ump.wav", CSoundMgr::MAXCHANNEL);
		float fX = owner->Get_Player()->Get_Info()->fX - owner->Get_Info()->fX + 100;
		float fY = owner->Get_Player()->Get_Info()->fY - owner->Get_Info()->fY;
		float fDist = sqrtf(fX * fX + fY * fY);

		float fAngle = acosf(fX / fDist);
		fAngle = (RADIANTODEGREE(fAngle));
		if (owner->Get_Info()->fY < owner->Get_Player()->Get_Info()->fY)
			fAngle = 360 - fAngle;

		owner->CreateRadial(fAngle);
		dwTime = GetTickCount();
		if (++iCount == 5)
			owner->Get_FSM()->ChangeState(CBossState_IDLE::Instance());
	}
	owner->FrameMove();
}

void CBossState_ATT3::Exit(CBoss * owner)
{
}

CBossState_ATT4::CBossState_ATT4()
{

}

CBossState_ATT4 * CBossState_ATT4::Instance()
{
	static CBossState_ATT4 Instance;
	return &Instance;
}

void CBossState_ATT4::Enter(CBoss * owner)
{
	owner->Set_FrameKey(L"Boss_Walk");
	owner->Set_Size(78, 140);
	owner->Set_Frame(0, 12, 0, 150);
	dwTime = GetTickCount();
	iCount = 0;
	fAngle = 0;
}

void CBossState_ATT4::Execute(CBoss * owner)
{
	if (dwTime + 50 < GetTickCount())
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Ump.wav", CSoundMgr::MAXCHANNEL);
		fAngle += 7.f;

		owner->CreateAtt(owner->Get_Info()->fX, owner->Get_Info()->fY, fAngle);
		owner->CreateAtt(owner->Get_Info()->fX, owner->Get_Info()->fY, 360 - fAngle);
		dwTime = GetTickCount();
		if (++iCount == 200)
			owner->Get_FSM()->ChangeState(CBossState_IDLE::Instance());
	}
	owner->FrameMove();
}

void CBossState_ATT4::Exit(CBoss * owner)
{
}

CBossState_STUN::CBossState_STUN()
{
}

CBossState_STUN * CBossState_STUN::Instance()
{
	static CBossState_STUN Instance;
	return &Instance;
}

void CBossState_STUN::Enter(CBoss * owner)
{
	dwTime = GetTickCount();
}

void CBossState_STUN::Execute(CBoss * owner)
{
	if (dwTime + 2000 < GetTickCount())
	{
		owner->Get_FSM()->ChangeState(CBossState_IDLE::Instance());
		dwTime = GetTickCount();
	}
	//if (owner->Get_Hp() <= 0)
	//	owner->Get_FSM()->ChangeState(CBossState_DEAD::Instance());
}

void CBossState_STUN::Exit(CBoss * owner)
{
}