#pragma once
#include "qComponent.h"

enum class DATA_TYPE
{
	INT,
	FLOAT,
	VEC2,
	OBJECT,
};

struct tBlackboardData
{
	DATA_TYPE	Type;
	void* pData;
};

class qState;

class qFSM : public qComponent
{
public:
	CLONE(qFSM);

	qFSM();
	~qFSM();


public:
	virtual void finaltick() override;


public:
	void AddState(const wstring& _strStateName, qState* _State);
	qState* FindState(const wstring& _strStateName);
	void ChangeState(const wstring& _strNextStateName);
	void SetBlackboardData(const wstring& _DataKey, DATA_TYPE _Type, void* _pData);

	template<typename T>
	T GetBlackboardData(const wstring& _DataKey);

private:
	static map<wstring, tBlackboardData>	m_mapGlobalData;

	map<wstring, tBlackboardData>			m_mapData;
	map<wstring, qState*>					m_mapState;
	qState* m_CurState;
};

template<typename T>
inline T qFSM::GetBlackboardData(const wstring& _DataKey)
{
	map<wstring, tBlackboardData>::iterator iter = m_mapData.find(_DataKey);

	assert(iter != m_mapData.end());

	if constexpr (std::is_same_v<int, T>)
	{
		assert(DATA_TYPE::INT == iter->second.Type);
		return *((T*)iter->second.pData);
	}

	if (std::is_same_v<float, T>)
	{
		assert(DATA_TYPE::FLOAT == iter->second.Type);
		return *((T*)iter->second.pData);
	}

	if (std::is_same_v<Vec2, T>)
	{
		assert(DATA_TYPE::VEC2 == iter->second.Type);
		return *((T*)iter->second.pData);
	}

	if constexpr (std::is_same_v<qObj*, T>)
	{
		assert(DATA_TYPE::OBJECT == iter->second.Type);
		return (T)iter->second.pData;
	}

	
}
