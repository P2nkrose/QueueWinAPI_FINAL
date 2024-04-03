#include "pch.h"
#include "qRedMoveState.h"

qRedMoveState::qRedMoveState()
	: m_Dir(1.f)
{
}

qRedMoveState::~qRedMoveState()
{
}

void qRedMoveState::Enter()
{
	init();

	m_CenterPos = GetObj()->GetCenterPos();

	if (DIRECTION::RIGHT == GetObj()->GetDir())
	{
		m_Dir = 1.f;
	}
	else if (DIRECTION::LEFT == GetObj()->GetDir())
	{
		m_Dir = -1.f;
	}

	if (m_Dir == 1.f)
	{
		GetAnimator()->Play(L"RedMoveRight", true);
	}
	else if (m_Dir == -1.f)
	{
		GetAnimator()->Play(L"RedMoveLeft", true);
	}
}

void qRedMoveState::FinalTick()
{
	qObj* pRed = GetBlackboardData<qObj*>(L"Red");
	float pRedSpeed = GetBlackboardData<float>(L"RedSpeed");
	float pMaxDist = GetBlackboardData<float>(L"MaxDist");
	int pRedHP = GetBlackboardData<int>(L"RedHP");

	Vec2 vPos = GetObj()->GetPos();


	vPos.x += m_Dir * pRedSpeed * DT;

	GetObj()->SetPos(vPos);

	float Dist = abs(m_CenterPos.x - vPos.x) - pMaxDist;
	if (10.f < Dist)
	{
		m_Dir *= -1.f;
		vPos.x += Dist * m_Dir;
		GetObj()->SetPos(vPos);

		if (m_Dir == -1.f)
		{
			GetObj()->SetDir(DIRECTION::LEFT);
			GetFSM()->ChangeState(L"RedIdle");
		}
		else if (m_Dir == 1.f)
		{
			GetObj()->SetDir(DIRECTION::RIGHT);
			GetFSM()->ChangeState(L"RedIdle");
		}
	}
}

void qRedMoveState::Exit()
{
}
