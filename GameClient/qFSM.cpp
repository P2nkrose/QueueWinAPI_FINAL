#include "pch.h"
#include "qFSM.h"

#include "qState.h"

qFSM::qFSM()
{
}

qFSM::~qFSM()
{
}

void qFSM::finaltick()
{
	if (nullptr == m_CurState)
		return;

	m_CurState->FinalTick();
}

void qFSM::AddState(const wstring& _strStateName, qState* _State)
{
	assert(!FindState(_strStateName));

	// ������ ������(FSM) �����ϱ�
	_State->m_Owner = this;

	// ���� �߰�
	m_mapState.insert(make_pair(_strStateName, _State));
}

qState* qFSM::FindState(const wstring& _strStateName)
{
	map<wstring, qState*>::iterator iter = m_mapState.find(_strStateName);

	if (iter == m_mapState.end())
	{
		return nullptr;
	}

	return iter->second;
}

void qFSM::ChangeState(const wstring& _strNextStateName)
{
	if (!m_CurState && (_strNextStateName == m_CurState->GetName()))
		return;

	if (nullptr != m_CurState)
		m_CurState->Exit();

	m_CurState = FindState(_strNextStateName);

	assert(m_CurState);

	m_CurState->Enter();
}
