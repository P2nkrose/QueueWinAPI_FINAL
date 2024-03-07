#pragma once
#include "qLevel.h"
class qLevel_Editor : public qLevel
{
public:
	qLevel_Editor();
	~qLevel_Editor();


private:
	virtual void begin() override;			
	virtual void tick() override;

	virtual void Enter() override;
	virtual void Exit() override;

};

