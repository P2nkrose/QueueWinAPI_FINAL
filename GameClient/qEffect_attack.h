#pragma once
#include "qObj.h"

class qSound;
class qAnimator;
class qTexture;

class qEffect_attack : public qObj
{
	CLONE(qEffect_attack);

public:
	qEffect_attack();
	qEffect_attack(const qEffect_attack& _Other);
	~qEffect_attack();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }

	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;

private:
	qAnimator*		m_Animator;
	qSound*			pSound;
};

