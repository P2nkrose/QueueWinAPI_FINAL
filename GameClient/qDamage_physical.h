#pragma once
#include "qObj.h"

class qAnimator;
class qTexture;

class qDamage_physical : public qObj
{
	CLONE(qDamage_physical);

public:
	qDamage_physical();
	~qDamage_physical();

	virtual void tick();

	qAnimator* GetAnimator() { return m_Animator; }

private:
	qAnimator* m_Animator;
};

