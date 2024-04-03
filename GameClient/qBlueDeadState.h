#pragma once
#include "qState.h"

class qSound;

class qBlueDeadState : public qState
{
public:
	CLONE(qBlueDeadState);

	qBlueDeadState();
	~qBlueDeadState();

public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


private:
	qSound*			pSound;

};

