#pragma once
#include "qObj.h"

class qSpawner_red1 : public qObj
{
public:

	CLONE(qSpawner_red1);

	qSpawner_red1();
	~qSpawner_red1();

public:
	virtual void begin() override;
	virtual void tick() override;




private:
	Vec2		m_Pos;
	float		m_Time;
};

