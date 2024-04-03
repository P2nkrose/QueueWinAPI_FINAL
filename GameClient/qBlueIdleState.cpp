#include "pch.h"
#include "qBlueIdleState.h"



qBlueIdleState::qBlueIdleState()
	: m_Time(0.f)
{
}

qBlueIdleState::~qBlueIdleState()
{
}


void qBlueIdleState::Enter()
{
	init();

	if (DIRECTION::RIGHT == GetObj()->GetDir())
	{
		GetAnimator()->Play(L"BlueIdleRight", true);
	}
	else if (DIRECTION::LEFT == GetObj()->GetDir())
	{
		GetAnimator()->Play(L"BlueIdleLeft", true);
	}
}


void qBlueIdleState::FinalTick()
{

	qObj* pBlue = GetBlackboardData<qObj*>(L"Blue");
	float pBlueSpeed = GetBlackboardData<float>(L"BlueSpeed");
	int pBlueHP = GetBlackboardData<int>(L"BlueHP");

	m_Time += DT;
	if (m_Time > 3.f)
	{
		GetFSM()->ChangeState(L"Move");
	}


	//	GetFSM()->ChangeState(L"Trace");

}

void qBlueIdleState::Exit()
{
	m_Time = 0.f;
}


