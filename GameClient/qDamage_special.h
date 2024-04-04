#pragma once
#include "qObj.h"

class qAnimator;

class qDamage_special : public qObj
{
	CLONE(qDamage_special);

public:
	qDamage_special();
	qDamage_special(const qDamage_special& _Other);
	~qDamage_special();

	virtual void tick();

	qAnimator* GetAnimator() { return m_Animator; }

private:
	qAnimator* m_Animator;
};

