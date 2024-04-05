#pragma once
#include "qObj.h"

class qSpawner_blue3 : public qObj
{
public:

	CLONE(qSpawner_blue3);

	qSpawner_blue3();
	~qSpawner_blue3();

public:
	virtual void begin() override;
	virtual void tick() override;




private:
	Vec2		m_Pos;
	float		m_Time;
};

