#pragma once
#include "qMissile.h"

class qGuideMissile : public qMissile
{
private:
	qObj*		m_Target;


public:
	virtual void tick() override;

public:
	qGuideMissile();
	~qGuideMissile();

};

