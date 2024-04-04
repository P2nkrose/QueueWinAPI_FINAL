#pragma once
#include "qObj.h"

class qAnimator;

class qDamage_missile : public qObj
{
	CLONE(qDamage_missile);

public:
	qDamage_missile();
	qDamage_missile(const qDamage_missile& _Other);
	~qDamage_missile();

	virtual void tick();

	qAnimator* GetAnimator() { return m_Animator; }

private:
	qAnimator* m_Animator;
};

