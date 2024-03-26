#include "pch.h"
#include "qFSM.h"

#include "qState.h"

qFSM::qFSM()
	: m_CurState(nullptr)
{
}

qFSM::qFSM(const qFSM& _Other)
	: qComponent(_Other)
	, m_CurState(nullptr)
{

}

qFSM::~qFSM()
{
	Safe_Del_Map(m_mapState);
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

	// 상태의 소유자(FSM) 세팅하기
	_State->m_Owner = this;

	// 상태 추가
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
	if (m_CurState && (_strNextStateName == m_CurState->GetName()))
		return;

	if (nullptr != m_CurState)
		m_CurState->Exit();

	m_CurState = FindState(_strNextStateName);

	assert(m_CurState);

	m_CurState->Enter();
}

void qFSM::SetBlackboardData(const wstring& _DataKey, DATA_TYPE _Type, void* _pData)
{
	tBlackboardData data = { _Type, _pData };
	m_mapData.insert(make_pair(_DataKey, data));
}
