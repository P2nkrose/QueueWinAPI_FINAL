#include "pch.h"
#include "qRedIdleState.h"

qRedIdleState::qRedIdleState()
	: m_Time(0.f)
{
}

qRedIdleState::~qRedIdleState()
{
}

void qRedIdleState::Enter()
{
	init();

	if (DIRECTION::RIGHT == GetObj()->GetDir())
	{
		GetAnimator()->Play(L"RedIdleRight", true);
	}
	else if (DIRECTION::LEFT == GetObj()->GetDir())
	{
		GetAnimator()->Play(L"RedIdleLeft", true);
	}
}

void qRedIdleState::FinalTick()
{
	qObj* pRed = GetBlackboardData<qObj*>(L"Red");
	float pRedSpeed = GetBlackboardData<float>(L"RedSpeed");
	int pRedHP = GetBlackboardData<int>(L"RedHP");

	m_Time += DT;
	if (m_Time > 3.f)
	{
		GetFSM()->ChangeState(L"RedMove");
	}

}

void qRedIdleState::Exit()
{
	m_Time = 0.f;
}
