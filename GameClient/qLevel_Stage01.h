#pragma once
#include "qLevel.h"

class qLevel_Stage01 : public qLevel
{
	CLONE(qLevel_Stage01);

public:
	qLevel_Stage01();
	~qLevel_Stage01();

	virtual void tick() override;
};

