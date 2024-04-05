#pragma once
#include "qObj.h"

class qSpawner_blue1 : public qObj
{
public:

	CLONE(qSpawner_blue1);

	qSpawner_blue1();
	~qSpawner_blue1();

public:
	virtual void begin() override;
	virtual void tick() override;




private:
	Vec2		m_Pos;
	float		m_Time;
};

