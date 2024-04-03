#include "pch.h"
#include "qBlueMoveState.h"

qBlueMoveState::qBlueMoveState()
	: m_Dir(1.f)
{
}

qBlueMoveState::~qBlueMoveState()
{
}

void qBlueMoveState::Enter()
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
		GetAnimator()->Play(L"BlueMoveRight", true);
	}
	else if (m_Dir == -1.f)
	{
		GetAnimator()->Play(L"BlueMoveLeft", true);
	}
}

void qBlueMoveState::FinalTick()
{
	qObj* pBlue = GetBlackboardData<qObj*>(L"Blue");
	float pBlueSpeed = GetBlackboardData<float>(L"BlueSpeed");
	float pMaxDist = GetBlackboardData<float>(L"MaxDist");
	int pBlueHP = GetBlackboardData<int>(L"BlueHP");

	Vec2 vPos = GetObj()->GetPos();


	vPos.x += m_Dir * pBlueSpeed * DT;

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
			GetFSM()->ChangeState(L"Idle");
		}
		else if (m_Dir == 1.f)
		{
			GetObj()->SetDir(DIRECTION::RIGHT);
			GetFSM()->ChangeState(L"Idle");
		}
	}

	

}

void qBlueMoveState::Exit()
{
}
