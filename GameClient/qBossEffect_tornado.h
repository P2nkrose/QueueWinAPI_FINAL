#pragma once
#include "qObj.h"

class qAnimator;
class qTexture;

class qBossEffect_tornado : public qObj
{
public:
	CLONE(qBossEffect_tornado);

	qBossEffect_tornado();
	~qBossEffect_tornado();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }

	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;

private:
	qAnimator* m_Animator;
};

