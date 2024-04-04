#pragma once
#include "qObj.h"

class qAnimator;
class qTexture;

class qDamage_miss : public qObj
{
	CLONE(qDamage_miss);

public:
	qDamage_miss();
	qDamage_miss(const qDamage_miss& _Other);
	~qDamage_miss();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }


private:
	qAnimator* m_Animator;
};

