#pragma once
#include "qEntity.h"
class qComponent : public qEntity
{
public:
	qComponent();
	~qComponent();


public:
	virtual void finaltick() = 0;
	virtual qComponent* Clone() = 0;


private:
};

