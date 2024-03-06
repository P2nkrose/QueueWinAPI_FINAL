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
	float& Range = GetFSM()->GetBlackboardData<float>(L"DetectRange");
	qObj& pSelf = GetFSM()->GetBlackboardData<qObj>(L"Self");


	// 플레이어가 감지되면, Trace 상태로 변경
}

void qIdleState::Exit()
{
}
