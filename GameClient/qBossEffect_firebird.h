#pragma once
#include "qObj.h"

class qAnimator;
class qTexture;

class qBossEffect_firebird : public qObj
{
public:
	CLONE(qBossEffect_firebird);

	qBossEffect_firebird();
	~qBossEffect_firebird();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }

	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;

private:
	qAnimator* m_Animator;
};

