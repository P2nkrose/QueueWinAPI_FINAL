#pragma once
#include "qEntity.h"

#include "qObj.h"

class qComponent : public qEntity
{
private:
	qObj*		m_Owner;		// ������Ʈ�� �����ϰ� �ִ� ������Ʈ



public:
	qObj* GetOwner() { return m_Owner; }



public:
	virtual void finaltick() = 0;
	virtual qComponent* Clone() = 0;


public:
	qComponent();
	~qComponent();

	friend class qObj;

};

