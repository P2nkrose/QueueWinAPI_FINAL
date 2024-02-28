#pragma once
#include "qState.h"
class qTraceState : public qState
{
public:

	CLONE(qTraceState);

	qTraceState();
	~qTraceState();

public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

private:


};

