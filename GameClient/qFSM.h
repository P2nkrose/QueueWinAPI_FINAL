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
	void*		pData;
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


private:
	static map<wstring, tBlackboardData>	m_mapGlobalData;

	map<wstring, tBlackboardData>			m_mapData;
	map<wstring, qState*>					m_mapState;
	qState*									m_CurState;


};

