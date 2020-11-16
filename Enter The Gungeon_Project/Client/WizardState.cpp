#include "stdafx.h"
#include "WizardState.h"
#include "AngleBullet.h"
#include "ObjMgr.h"

CWizardState::CWizardState()
{
}


CWizardState::~CWizardState()
{
}

CWizardState_IDLE * CWizardState_IDLE::Instance()
{
	static CWizardState_IDLE Instance;
	return &Instance;
}

void CWizardState_IDLE::Enter(CWizard * owner)
{
	owner->Set_Frame(0, 5, 0, 200);
}

void CWizardState_IDLE::Execute(CWizard * owner)
{
	float fX = owner->Get_Player()->Get_Info()->fX - owner->Get_Info()->fX;
	float fY = owner->Get_Player()->Get_Info()->fY - owner->Get_Info()->fY;
	float fDist = sqrtf(fX * fX + fY * fY);
	if (fDist < SHOT)
	{
		owner->Get_FSM()->ChangeState(CWizardState_SHOT::Instance());
	}
	else if (fDist < FOLLOW)
	{
		owner->Get_FSM()->ChangeState(CWizardState_FOLLOW::Instance());
	}
}

void CWizardState_IDLE::Exit(CWizard * owner)
{
}

CWizardState_FOLLOW * CWizardState_FOLLOW::Instance()
{
	static CWizardState_FOLLOW Instance;
	return &Instance;
}

void CWizardState_FOLLOW::Enter(CWizard * owner)
{
}

void CWizardState_FOLLOW::Execute(CWizard * owner)
{
	float fX = owner->Get_Player()->Get_Info()->fX - owner->Get_Info()->fX;
	float fY = owner->Get_Player()->Get_Info()->fY - owner->Get_Info()->fY;
	float fDist = sqrtf(fX * fX + fY * fY);

	float fAngle = acosf(fX / fDist);
	owner->Set_Angle(RADIANTODEGREE(fAngle));
	if (owner->Get_Info()->fY < owner->Get_Player()->Get_Info()->fY)
		owner->Set_Angle(360.f - owner->Get_Angle());

	if (90 < owner->Get_Angle() && owner->Get_Angle() <= 270)
	{
		if (owner->Get_Dir() != MONSTER::LEFT)
		{
			owner->Set_Frame(0, 5, 1, 200);
			owner->Set_Dir(MONSTER::LEFT);
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

	owner->Move_Pos(cosf(DEGREETORADIAN(owner->Get_Angle())) * owner->Get_Speed(), -sinf(DEGREETORADIAN(owner->Get_Angle())) * owner->Get_Speed());
	if (fDist < SHOT)
	{
		owner->Get_FSM()->ChangeState(CWizardState_SHOT::Instance());
	}
	else if (fDist >= FOLLOW)
	{
		owner->Get_FSM()->ChangeState(CWizardState_IDLE::Instance());
	}
	owner->FrameMove();
}

void CWizardState_FOLLOW::Exit(CWizard * owner)
{
}

CWizardState_SHOT * CWizardState_SHOT::Instance()
{
	static CWizardState_SHOT Instance;
	return &Instance;
}

void CWizardState_SHOT::Enter(CWizard * owner)
{
	m_dwTime = GetTickCount();
	owner->Set_Frame(0, 5, 2, 200);
}

void CWizardState_SHOT::Execute(CWizard * owner)
{
	if (owner->Get_Count() == 0)
	{
		if (owner->Get_lstBulet()->size() > 36)
		{
			float fX = owner->Get_Player()->Get_Info()->fX - owner->Get_Info()->fX;
			float fY = owner->Get_Player()->Get_Info()->fY - owner->Get_Info()->fY;
			float fDist = sqrtf(fX * fX + fY * fY);

			float fAngle = acosf(fX / fDist);
			owner->Set_Angle(RADIANTODEGREE(fAngle));
			if (owner->Get_Info()->fY < owner->Get_Player()->Get_Info()->fY)
				owner->Set_Angle(360.f - owner->Get_Angle());
			for (auto& pBullet : *owner->Get_lstBulet())
			{
				pBullet->Set_Angle(owner->Get_Angle());
				CAST<CAngleBullet*>(pBullet)->Set_Move(true);
			}
			CSoundMgr::Get_Instance()->PlaySound(L"Ump.wav", CSoundMgr::MAXCHANNEL);
			owner->Get_lstBulet()->clear();
			owner->Set_ShotAngle(0.f);
			owner->Get_FSM()->ChangeState(CWizardState_COOL::Instance());
		}
		else if (m_dwTime + 20 < GetTickCount())
		{
			owner->CreateBullet(owner->Get_Info()->fX + cosf(DEGREETORADIAN((owner)->Get_ShotAngle())) * owner->Get_Dist(),
				owner->Get_Info()->fY - sinf(DEGREETORADIAN((owner)->Get_ShotAngle())) * owner->Get_Dist());
			owner->Set_ShotAngle(owner->Get_ShotAngle() + 10.f);
			m_dwTime = GetTickCount();
		}
	}
	else if(owner->Get_Count() == 1)
	{
		if (owner->Get_ShapeCount() < 8)
		{
			if (m_dwTime + 30 < GetTickCount())
			{
				owner->CreateBullet(owner->Get_Info()->fX - 80 + 20 * owner->Get_ShapeCount(), 
					owner->Get_Info()->fY - 80);
				owner->Plus_ShapeCount();
				m_dwTime = GetTickCount();
			}
		}
		else if (owner->Get_ShapeCount() < 16)
		{
			if (m_dwTime + 30 < GetTickCount())
			{
				owner->CreateBullet(owner->Get_Info()->fX + 80,
					owner->Get_Info()->fY - 80 + 20 * (owner->Get_ShapeCount() - 8));
				owner->Plus_ShapeCount();
				m_dwTime = GetTickCount();
			}
		}
		else if (owner->Get_ShapeCount() < 24)
		{
			if (m_dwTime + 30 < GetTickCount())
			{
				owner->CreateBullet(owner->Get_Info()->fX + 80 - 20 * (owner->Get_ShapeCount() - 16),
					owner->Get_Info()->fY + 80);
				owner->Plus_ShapeCount();
				m_dwTime = GetTickCount();
			}
		}
		else if (owner->Get_ShapeCount() < 32)
		{
			if (m_dwTime + 30 < GetTickCount())
			{
				owner->CreateBullet(owner->Get_Info()->fX - 80,
					owner->Get_Info()->fY + 80 - 20 * (owner->Get_ShapeCount() - 24));
				owner->Plus_ShapeCount();
				m_dwTime = GetTickCount();
			}
		}
		else
		{
			float fX = owner->Get_Player()->Get_Info()->fX - owner->Get_Info()->fX;
			float fY = owner->Get_Player()->Get_Info()->fY - owner->Get_Info()->fY;
			float fDist = sqrtf(fX * fX + fY * fY);

			float fAngle = acosf(fX / fDist);
			owner->Set_Angle(RADIANTODEGREE(fAngle));
			if (owner->Get_Info()->fY < owner->Get_Player()->Get_Info()->fY)
				owner->Set_Angle(360.f - owner->Get_Angle());
			for (auto& pBullet : *owner->Get_lstBulet())
			{
				pBullet->Set_Angle(owner->Get_Angle());
				CAST<CAngleBullet*>(pBullet)->Set_Move(true);
			}
			CSoundMgr::Get_Instance()->PlaySound(L"Ump.wav", CSoundMgr::MAXCHANNEL);
			owner->Get_lstBulet()->clear();
			owner->Set_ShotAngle(0.f);
			owner->Set_ShapeCount();
			owner->Get_FSM()->ChangeState(CWizardState_COOL::Instance());
		}
	}
	else if (owner->Get_Count() == 2)
	{
		if (owner->Get_ShapeCount() < 8)
		{
			if (m_dwTime + 40 < GetTickCount())
			{
				owner->CreateBullet(owner->Get_Info()->fX + 10 * owner->Get_ShapeCount(),
					owner->Get_Info()->fY - 80 + 20 * owner->Get_ShapeCount());
				owner->Plus_ShapeCount();
				m_dwTime = GetTickCount();
			}
		}
		else if (owner->Get_ShapeCount() < 16)
		{
			if (m_dwTime + 40 < GetTickCount())
			{
				owner->CreateBullet(owner->Get_Info()->fX + 80 - 20 * (owner->Get_ShapeCount() - 8),
					owner->Get_Info()->fY + 80);
				owner->Plus_ShapeCount();
				m_dwTime = GetTickCount();
			}
		}
		else if (owner->Get_ShapeCount() < 24)
		{
			if (m_dwTime + 40 < GetTickCount())
			{
				owner->CreateBullet(owner->Get_Info()->fX - 80 + 10 * (owner->Get_ShapeCount() - 16),
					owner->Get_Info()->fY + 80 - 20 * (owner->Get_ShapeCount() - 16));
				owner->Plus_ShapeCount();
				m_dwTime = GetTickCount();
			}
		}
		else
		{
			float fX = owner->Get_Player()->Get_Info()->fX - owner->Get_Info()->fX;
			float fY = owner->Get_Player()->Get_Info()->fY - owner->Get_Info()->fY;
			float fDist = sqrtf(fX * fX + fY * fY);

			float fAngle = acosf(fX / fDist);
			owner->Set_Angle(RADIANTODEGREE(fAngle));
			if (owner->Get_Info()->fY < owner->Get_Player()->Get_Info()->fY)
				owner->Set_Angle(360.f - owner->Get_Angle());
			for (auto& pBullet : *owner->Get_lstBulet())
			{
				pBullet->Set_Angle(owner->Get_Angle());
				CAST<CAngleBullet*>(pBullet)->Set_Move(true);
			}
			CSoundMgr::Get_Instance()->PlaySound(L"Ump.wav", CSoundMgr::MAXCHANNEL);
			owner->Get_lstBulet()->clear();
			owner->Set_ShotAngle(0.f);
			owner->Set_ShapeCount();
			owner->Get_FSM()->ChangeState(CWizardState_COOL::Instance());
		}
	}
	owner->FrameMove();
}

void CWizardState_SHOT::Exit(CWizard * owner)
{
	owner->Plus_Count();
	if (!owner->Get_lstBulet()->empty())
	{
		for (auto& iter = owner->Get_lstBulet()->begin(); iter != owner->Get_lstBulet()->end(); ++iter)
		{
			auto& finditer = find(CObjMgr::Get_Instance()->Get_M_LstBullet()->begin(), CObjMgr::Get_Instance()->Get_M_LstBullet()->end(), *iter);
			if (finditer != CObjMgr::Get_Instance()->Get_M_LstBullet()->end())
			{
				delete *finditer;
				CObjMgr::Get_Instance()->Get_M_LstBullet()->erase(finditer);
			}
		}
		owner->Get_lstBulet()->clear();
	}
}

CWizardState_STUN * CWizardState_STUN::Instance()
{
	static CWizardState_STUN Instance;
	return &Instance;
}

void CWizardState_STUN::Enter(CWizard * owner)
{
	dwTime = GetTickCount();
	//가지고 있는 총알 있으면 삭제
}

void CWizardState_STUN::Execute(CWizard * owner)
{
	if (dwTime + 2000 < GetTickCount())
	{
		owner->Get_FSM()->ChangeState(CWizardState_IDLE::Instance());
		dwTime = GetTickCount();
	}
}

void CWizardState_STUN::Exit(CWizard * owner)
{
}

CWizardState_COOL * CWizardState_COOL::Instance()
{
	static CWizardState_COOL Instance;
	return &Instance;
}

void CWizardState_COOL::Enter(CWizard * owner)
{
	dwTime = GetTickCount();
}

void CWizardState_COOL::Execute(CWizard * owner)
{
	if (dwTime + 1000 < GetTickCount())
	{
		owner->Get_FSM()->ChangeState(CWizardState_IDLE::Instance());
		dwTime = GetTickCount();
	}
}

void CWizardState_COOL::Exit(CWizard * owner)
{
}
