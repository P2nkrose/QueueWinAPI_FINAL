#pragma once
#include "qObj.h"

class qAnimator;
class qTexture;

class qBossEffect_genesis : public qObj
{
	CLONE(qBossEffect_genesis);

public:
	qBossEffect_genesis();
	~qBossEffect_genesis();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }

	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;

private:
	qAnimator* m_Animator;
};

