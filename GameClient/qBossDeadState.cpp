#include "pch.h"
#include "qBossDeadState.h"

qBossDeadState::qBossDeadState()
	: m_Time(0.f)
	, m_Dir(-1.f)
{
}

qBossDeadState::~qBossDeadState()
{
}

void qBossDeadState::Enter()
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
		GetAnimator()->Play(L"BossDeadRight", false);
	}
	else if (m_Dir == -1.f)
	{
		GetAnimator()->Play(L"BossDeadLeft", false);
	}
}

void qBossDeadState::FinalTick()
{
	qObj* pBoss = GetBlackboardData<qObj*>(L"Boss");
	int pBossHP = GetBlackboardData<int>(L"BossHP");

	if (L"BossDeadRight" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->IsFinish())
		{
			GetObj()->Destroy();
		}
	}

	if (L"BossDeadLeft" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->IsFinish())
		{
			GetObj()->Destroy();
		}
	}
}

void qBossDeadState::Exit()
{
}
