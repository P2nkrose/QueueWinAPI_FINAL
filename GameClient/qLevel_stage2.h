#pragma once
#include "qLevel.h"

class qSound;

class qLevel_stage2 : public qLevel
{
public:
	qLevel_stage2();
	~qLevel_stage2();

public:

	virtual void begin() override;
	virtual void tick() override;

	virtual void Enter() override;
	virtual void Exit() override;

private:
	qSound*		pSound;
};

