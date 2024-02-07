#pragma once
#include "qMissile.h"

class qGuideMissile : public qMissile
{
private:
	qObj*		m_Target;
	float       m_Range;

public:
	virtual void tick() override;


private:
	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;
	void FindTarget();

public:
	qGuideMissile();
	~qGuideMissile();

};

