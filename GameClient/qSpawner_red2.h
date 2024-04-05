#pragma once
#include "qObj.h"

class qSpawner_red2 : public qObj
{
public:

	CLONE(qSpawner_red2);

	qSpawner_red2();
	~qSpawner_red2();

public:
	virtual void begin() override;
	virtual void tick() override;




private:
	Vec2		m_Pos;
	float		m_Time;
};

