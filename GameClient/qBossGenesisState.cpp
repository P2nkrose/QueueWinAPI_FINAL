#include "pch.h"
#include "qBossGenesisState.h"

qBossGenesisState::qBossGenesisState()
	: m_Time(0.f)
	, m_Dir(-1.f)
{
}

qBossGenesisState::~qBossGenesisState()
{
}

void qBossGenesisState::Enter()
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
		GetAnimator()->Play(L"BossGenesisRight", false);
	}
	else if (m_Dir == -1.f)
	{
		GetAnimator()->Play(L"BossGenesisLeft", false);
	}
}

void qBossGenesisState::FinalTick()
{
	qObj* pBoss = GetBlackboardData<qObj*>(L"Boss");
	int pBossHP = GetBlackboardData<int>(L"BossHP");


	if (L"BossGenesisRight" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->IsFinish())
		{
			GetFSM()->ChangeState(L"Idle");
		}
	}

	if (L"BossGenesisLeft" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->IsFinish())
		{
			GetFSM()->ChangeState(L"Idle");
		}
	}
}

void qBossGenesisState::Exit()
{
}
