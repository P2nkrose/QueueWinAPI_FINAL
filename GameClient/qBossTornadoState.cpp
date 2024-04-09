#include "pch.h"
#include "qBossTornadoState.h"

qBossTornadoState::qBossTornadoState()
	: m_Time(0.f)
	, m_Dir(-1.f)
{

}

qBossTornadoState::~qBossTornadoState()
{
	
}

void qBossTornadoState::Enter()
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
		GetAnimator()->Play(L"BossTornadoRight", false);
	}
	else if (m_Dir == -1.f)
	{
		GetAnimator()->Play(L"BossTornadoLeft", false);
	}
}

void qBossTornadoState::FinalTick()
{
	qObj* pBoss = GetBlackboardData<qObj*>(L"Boss");
	int pBossHP = GetBlackboardData<int>(L"BossHP");

	if (L"BossTornadoRight" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->IsFinish())
		{
			GetFSM()->ChangeState(L"Idle");
		}
	}

	if (L"BossTornadoLeft" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->IsFinish())
		{
			GetFSM()->ChangeState(L"Idle");
		}
	}
}

void qBossTornadoState::Exit()
{
}
