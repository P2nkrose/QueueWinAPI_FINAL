#pragma once
#include "qLevel.h"

class qSound;

class qLevel_Start : public qLevel
{
public:
	qLevel_Start();
	~qLevel_Start();

public:
	virtual void begin() override;

	virtual void Enter() override;
	virtual void Exit() override;


private:
	qSound* pSound;
};

