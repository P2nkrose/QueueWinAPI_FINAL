#pragma once
#include "qLevel.h"

class qSound;
class qAnimator;

class qLevel_Logo : public qLevel
{
public:
	qLevel_Logo();
	~qLevel_Logo();


public:
	virtual void begin() override;
	virtual void tick() override;
	virtual void Enter() override;
	virtual void Exit() override;


private:
	qSound*			pSound;
	//qAnimator*		m_Animator;

};

