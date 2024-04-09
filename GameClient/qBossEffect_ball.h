#pragma once
#include "qObj.h"

class qAnimator;
class qTexture;

class qBossEffect_ball : public qObj
{
	CLONE(qBossEffect_ball);

public:
	qBossEffect_ball();
	~qBossEffect_ball();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }

	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;

private:
	qAnimator*		m_Animator;
};

