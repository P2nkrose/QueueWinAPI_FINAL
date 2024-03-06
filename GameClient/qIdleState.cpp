#include "pch.h"
#include "qIdleState.h"

qIdleState::qIdleState()
{
}

qIdleState::~qIdleState()
{
}

void qIdleState::Enter()
{
}

void qIdleState::FinalTick()
{
	// 근처 (탐지 범위) 에 플레이어가 있는지 탐지
	// float fRange = GetBlackboardData(L"DetectRage");
	float Range = GetBlackboardData<float>(L"DetectRange");
	qObj* pSelf = GetBlackboardData<qObj*>(L"Self");
	qObj* pPlayer = GetBlackboardData<qObj*>(L"Target");

	// 몬스터의 탐지 범위를 시각화한다.
	DrawDebugCircle(PEN_TYPE::PEN_GREEN, pSelf->GetRenderPos(), Vec2(Range * 2.f, Range * 2.f), 0);

	// 플레이어가 감지되면, Trace 상태로 변경
	if (pPlayer->GetPos().GetDistance(pSelf->GetPos()) < Range)
	{
		GetFSM()->ChangeState(L"Trace");
	}
}

void qIdleState::Exit()
{
}
