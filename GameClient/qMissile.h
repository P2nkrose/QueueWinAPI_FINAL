#pragma once
#include "qObj.h"
class qMissile : public qObj
{
public:
	qMissile();
	~qMissile();


public:
	virtual void tick() override;
	virtual void render() override;


private:
	virtual qMissile* Clone() { return new qMissile(*this); }


private:
	float		m_Speed;
	qCollider*	m_Collider;

};

