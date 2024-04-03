#pragma once
#include "qEntity.h"

#include "qFSM.h"

#include "qAnimation.h"
#include "qAnimator.h"
#include "qRigidbody.h"
#include "qCollider.h"

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

	template<typename T>
	T GetBlackboardData(const wstring& _DataName)
	{
		return m_Owner->GetBlackboardData<T>(_DataName);
	}

	void init();

public:
	void SetDir(DIRECTION _Dir) { m_Dir = _Dir; }
	DIRECTION GetDir() { return m_Dir; }

public:
	qAnimator* GetAnimator() { return m_Animator; }

private:
	DIRECTION		m_Dir;


private:
	qFSM*			m_Owner;
	qAnimator*		m_Animator;
	qRigidbody*		m_Rigidbody;
	qCollider*		m_Collider;
};

