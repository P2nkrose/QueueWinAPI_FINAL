#pragma once
#include "qObj.h"

class qCamera;
class qTexture;
class qAnimator;

class qBackground_start : public qObj
{
public:
	CLONE(qBackground_start);


public:
	qBackground_start();
	qBackground_start(const qBackground_start& _Other);
	~qBackground_start();

	qAnimator* GetAnimator() { return m_Animator; }

	virtual void tick() override;


private:
	qAnimator*		m_Animator;
};

