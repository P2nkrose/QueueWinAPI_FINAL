#pragma once
#include "qLevel.h"

class qSound;

class qStart : public qLevel
{
public:
	qStart();
	~qStart();

public:
	virtual void begin() override;

	virtual void Enter() override;
	virtual void Exit() override;


private:
	qSound* pSound;
};

