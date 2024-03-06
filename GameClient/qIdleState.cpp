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
	// ��ó (Ž�� ����) �� �÷��̾ �ִ��� Ž��
	// float fRange = GetBlackboardData(L"DetectRage");
	float Range = GetBlackboardData<float>(L"DetectRange");
	qObj* pSelf = GetBlackboardData<qObj*>(L"Self");
	qObj* pPlayer = GetBlackboardData<qObj*>(L"Target");

	// ������ Ž�� ������ �ð�ȭ�Ѵ�.
	DrawDebugCircle(PEN_TYPE::PEN_GREEN, pSelf->GetRenderPos(), Vec2(Range * 2.f, Range * 2.f), 0);

	// �÷��̾ �����Ǹ�, Trace ���·� ����
	if (pPlayer->GetPos().GetDistance(pSelf->GetPos()) < Range)
	{
		GetFSM()->ChangeState(L"Trace");
	}
}

void qIdleState::Exit()
{
}
