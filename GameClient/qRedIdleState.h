#pragma once
#include "qState.h"

class qRedIdleState : public qState
{
public:
	CLONE(qRedIdleState);

	qRedIdleState();
	~qRedIdleState();

public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;



private:
	Vec2		m_Pos;
	float		m_Time;
};

