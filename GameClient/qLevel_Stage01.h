#pragma once
#include "qLevel.h"
class qLevel_Stage01 : public qLevel
{
private:


public:
	virtual qLevel_Stage01* Clone() override { return new qLevel_Stage01(*this); };

public:
	qLevel_Stage01();
	~qLevel_Stage01();
};

