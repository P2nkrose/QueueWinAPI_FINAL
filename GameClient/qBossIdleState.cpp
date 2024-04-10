#include "pch.h"
#include "qBossIdleState.h"


qBossIdleState::qBossIdleState()
	: m_Time(0.f)
	, m_Dir(-1.f)
{
}

qBossIdleState::~qBossIdleState()
{
}

void qBossIdleState::Enter()
{
	init();

	m_CenterPos = GetObj()->GetCenterPos();

	if (DIRECTION::LEFT == GetObj()->GetDir())
	{
		m_Dir = -1.f;
	}
	else if (DIRECTION::RIGHT == GetObj()->GetDir())
	{
		m_Dir = 1.f;
	}

	if (m_Dir == 1.f)
	{
		GetAnimator()->Play(L"BossIdleRight", true);
	}
	else if (m_Dir == -1.f)
	{
		GetAnimator()->Play(L"BossIdleLeft", true);
	}
	
}

void qBossIdleState::FinalTick()
{

	qObj* pPlayer = GetBlackboardData<qObj*>(L"Player");

	Vec2 PlayerPos = pPlayer->GetPos();
	Vec2 PlayerPrevPos = pPlayer->GetPrevPos();

	float fDist = m_CenterPos.x - PlayerPos.x;
	float PrevDir = m_Dir;

	if (fDist < 0)
	{
		SetDir(1.f);
	}
	else if (fDist > 0)
	{
		SetDir(-1.f);
	}

	if (m_Dir == 1.f && PrevDir != m_Dir)
	{
		GetAnimator()->Play(L"BossIdleRight", true);
		GetObj()->SetDir(DIRECTION::RIGHT);
	}
	else if (m_Dir == -1.f && PrevDir != m_Dir)
	{
		GetAnimator()->Play(L"BossIdleLeft", true);
		GetObj()->SetDir(DIRECTION::LEFT);
	}



	qObj* pBoss = GetBlackboardData<qObj*>(L"Boss");

	int state = rand() % 4;

	m_Time += DT;
	if (m_Time > 3.f)
	{
		if (state == 0)
		{
			GetFSM()->ChangeState(L"Ball");
		}
		else if (state == 1)
		{
			GetFSM()->ChangeState(L"Genesis");
		}
		else if (state == 2)
		{
			GetFSM()->ChangeState(L"Firebird");
		}
		else if (state == 3)
		{
			GetFSM()->ChangeState(L"Tornado");
		}
	}
}

void qBossIdleState::Exit()
{
	m_Time = 0.f;
}
