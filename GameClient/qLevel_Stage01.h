#pragma once
#include "qLevel.h"

class qLevel_Stage01 : public qLevel
{
public:
	qLevel_Stage01();
	~qLevel_Stage01();

	virtual void begin() override;
	virtual void tick() override;

	virtual void Enter() override;
	virtual void Exit() override;
};


