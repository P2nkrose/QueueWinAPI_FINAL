#pragma once
#include "qObj.h"

class qAnimator;

class qDamage_slash : public qObj
{
	CLONE(qDamage_slash);

public:
	qDamage_slash();
	qDamage_slash(const qDamage_slash& _Other);
	~qDamage_slash();

	virtual void tick();

	qAnimator* GetAnimator() { return m_Animator; }

private:
	qAnimator* m_Animator;
};

