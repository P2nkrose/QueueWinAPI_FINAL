#pragma once
#include "qState.h"
class qPlayerState : public qState
{
public:
	CLONE(qPlayerState);

public:
	qPlayerState();
	~qPlayerState();

private:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

};

