#pragma once
#include "qObj.h"


class qMonster : public qObj
{
public:
	qMonster();
	~qMonster();

public:
	virtual void tick() override;
	virtual void render() override;
	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;




	virtual qMonster* Clone() { return new qMonster(*this); }


private:

	int			m_HP;

	qCollider*	m_Collider;
};

