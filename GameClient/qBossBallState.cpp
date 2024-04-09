#include "pch.h"
#include "qBossBallState.h"


qBossBallState::qBossBallState()
	: m_Time(0.f)
	, m_Dir(-1.f)
{
}

qBossBallState::~qBossBallState()
{
}

void qBossBallState::Enter()
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
		GetAnimator()->Play(L"BossBallRight", false);
	}
	else if (m_Dir == -1.f)
	{
		GetAnimator()->Play(L"BossBallLeft", false);
	}
}

void qBossBallState::FinalTick()
{
	//qObj* pPlayer = GetBlackboardData<qObj*>(L"Player");

	//Vec2 PlayerPos = pPlayer->GetPos();
	//Vec2 PlayerPrevPos = pPlayer->GetPrevPos();

	//float fDist = m_CenterPos.x - PlayerPos.x;
	//float PrevDir = m_Dir;

	//if (fDist < 0)
	//{
	//	SetDir(1.f);
	//}
	//else if (fDist > 0)
	//{
	//	SetDir(-1.f);
	//}

	//if (m_Dir == 1.f && PrevDir != m_Dir)
	//{
	//	GetAnimator()->Play(L"BossBallRight", false);
	//}
	//else if (m_Dir == -1.f && PrevDir != m_Dir)
	//{
	//	GetAnimator()->Play(L"BossBallLeft", false);
	//}

	qObj* pBoss = GetBlackboardData<qObj*>(L"Boss");
	int pBossHP = GetBlackboardData<int>(L"BossHP");


	if (L"BossBallRight" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->IsFinish())
		{
			GetFSM()->ChangeState(L"Idle");
		}
	}

	if (L"BossBallLeft" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->IsFinish())
		{
			GetFSM()->ChangeState(L"Idle");
		}
	}
	
	
}

void qBossBallState::Exit()
{
}
