#pragma once
#include "qState.h"

class qBlueIdleState : public qState
{
public:
	
	CLONE(qBlueIdleState);
	
	qBlueIdleState();
	~qBlueIdleState();

public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;



private:
	Vec2			m_Pos;
	float			m_Time;
};

