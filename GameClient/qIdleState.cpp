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
	float& Range = GetFSM()->GetBlackboardData<float>(L"DetectRange");
	qObj& pSelf = GetFSM()->GetBlackboardData<qObj>(L"Self");


	// �÷��̾ �����Ǹ�, Trace ���·� ����
}

void qIdleState::Exit()
{
}
