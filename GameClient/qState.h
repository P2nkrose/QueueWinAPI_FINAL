#pragma once
#include "qEntity.h"

#include "qFSM.h"
class qState : public qEntity
{
public:

	friend class qFSM;

	qState();
	~qState();

public:

	virtual void Enter() PURE;
	virtual void FinalTick() PURE;
	virtual void Exit() PURE;

protected:
	qObj* GetObj() { return m_Owner->GetOwner(); }
	qFSM* GetFSM() { return m_Owner; }

	void* GetBlackboardData(const wstring& _DataName)
	{
		//return m_Owner->GetBlackboardData(_DataName);
	}

private:
	qFSM*	m_Owner;
};

