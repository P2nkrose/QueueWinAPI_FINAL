#pragma once
#include "qObj.h"

class qCollider;

class qPlayer : public qObj
{
private:
	float		m_Speed;

	qCollider*	m_Collider;

public:
	virtual void begin();
	virtual void tick();		
	virtual void render();


public:
	virtual qObj* Clone() override { return new qPlayer(*this); };


public:
	qPlayer();
	~qPlayer();

};

