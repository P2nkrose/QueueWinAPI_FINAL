#pragma once
#include "qObj.h"

class qCamera;
class qTexture;
class qAnimator;

class qLogo : public qObj
{
public:
	CLONE(qLogo);

public:
	qLogo();
	qLogo(const qLogo& _Other);
	~qLogo();

	qAnimator* GetAnimator() { return m_Animator; }

	virtual void tick() override;

private:
	qAnimator*		m_Animator;
};

