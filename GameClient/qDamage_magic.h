#pragma once
#include "qObj.h"

class qAnimator;
class qTexture;

class qDamage_magic : public qObj
{
	CLONE(qDamage_magic);

public:
	qDamage_magic();
	~qDamage_magic();

	virtual void tick();

	qAnimator* GetAnimator() { return m_Animator; }

private:
	qAnimator* m_Animator;
};

