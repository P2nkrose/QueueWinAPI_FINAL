#pragma once
#include "qLevel.h"


class qLogo : public qLevel
{
public:
	qLogo();
	~qLogo();


public:
	virtual void begin() override;
	virtual void render() override;

	virtual void Enter() override;
	virtual void Exit() override;



};

