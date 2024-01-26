#pragma once
#include "qObj.h"

class qPlayer : public qObj
{
private:
	float	m_Speed;


public:
	virtual void begin();
	virtual void tick();		
	virtual void finaltick();
	virtual void render();


public:
	virtual qObj* Clone() override { return new qPlayer(*this); };


public:
	qPlayer();
	~qPlayer();

};

