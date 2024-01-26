#pragma once
#include "qObj.h"
class qMissile : public qObj
{
private:
	virtual qMissile* Clone() { return new qMissile(*this); }


public:
	qMissile();
	~qMissile();


public:
	virtual void tick() override;


private:
	float		m_Speed;


};

