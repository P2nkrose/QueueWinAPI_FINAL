#pragma once
#include "qEntity.h"

#include "qObj.h"

class qComponent : public qEntity
{
private:
	qObj*		m_Owner;		// 컴포넌트를 소유하고 있는 오브젝트



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

