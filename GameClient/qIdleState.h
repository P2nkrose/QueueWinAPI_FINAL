#pragma once
#include "qState.h"

class qIdleState : public qState
{
public:
	
	CLONE(qIdleState);
	
	qIdleState();
	~qIdleState();

public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

private:
	
};

