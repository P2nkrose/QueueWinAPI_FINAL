#include "pch.h"
#include "qBossFirebirdState.h"

qBossFirebirdState::qBossFirebirdState()
	: m_Time(0.f)
	, m_Dir(-1.f)
{
}

qBossFirebirdState::~qBossFirebirdState()
{
}

void qBossFirebirdState::Enter()
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
		GetAnimator()->Play(L"BossFirebirdRight", false);
	}
	else if (m_Dir == -1.f)
	{
		GetAnimator()->Play(L"BossFirebirdLeft", false);
	}
}

void qBossFirebirdState::FinalTick()
{
	qObj* pBoss = GetBlackboardData<qObj*>(L"Boss");
	int pBossHP = GetBlackboardData<int>(L"BossHP");


	if (L"BossFirebirdRight" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->IsFinish())
		{
			GetFSM()->ChangeState(L"Idle");
		}
	}

	if (L"BossFirebirdLeft" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->IsFinish())
		{
			GetFSM()->ChangeState(L"Idle");
		}
	}
}

void qBossFirebirdState::Exit()
{
}



