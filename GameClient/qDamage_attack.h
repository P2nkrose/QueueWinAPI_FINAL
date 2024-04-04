#pragma once
#include "qObj.h"

class qAnimator;
class qTexture;

class qDamage_attack : public qObj
{
	CLONE(qDamage_attack);

public:
	qDamage_attack();
	qDamage_attack(const qDamage_attack& _Other);
	~qDamage_attack();

	virtual void tick();

	qAnimator* GetAnimator() { return m_Animator; }

private:
	qAnimator* m_Animator;
};

