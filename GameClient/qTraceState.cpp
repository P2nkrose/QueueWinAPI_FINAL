#include "pch.h"
#include "qTraceState.h"

qTraceState::qTraceState()
{
}

qTraceState::~qTraceState()
{
}

void qTraceState::Enter()
{
}

void qTraceState::FinalTick()
{
	float Range = GetBlackboardData<float>(L"DetectRange");
	float Speed = GetBlackboardData<float>(L"Speed");
	qObj* pSelf = GetBlackboardData<qObj*>(L"Self");
	qObj* pPlayer = GetBlackboardData<qObj*>(L"Target");

	// 플레이어를 추적한다.
	Vec2 vDir = pPlayer->GetPos() - pSelf->GetPos();
	
	if (!vDir.IsZero())
	{
		vDir.Normalize();
		Vec2 vPos = pSelf->GetPos() + (vDir * Speed * DT);
		pSelf->SetPos(vPos);
	}

}

void qTraceState::Exit()
{
}
