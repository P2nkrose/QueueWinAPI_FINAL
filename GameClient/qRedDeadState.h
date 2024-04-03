#pragma once
#include "qState.h"

class qSound;

class qRedDeadState : public qState
{
public:
	CLONE(qRedDeadState);

	qRedDeadState();
	~qRedDeadState();

public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


private:
	qSound*			pSound;
};

