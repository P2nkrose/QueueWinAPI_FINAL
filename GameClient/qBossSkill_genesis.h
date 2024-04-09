#pragma once
#include "qObj.h"

class qCamera;
class qTexture;
class qAnimator;

class qBossSkill_genesis : public qObj
{
	CLONE(qBossSkill_genesis);

public:

	qBossSkill_genesis();
	~qBossSkill_genesis();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }
	qCollider* GetCollider() { return m_Collider; }

	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;

private:
	qAnimator* m_Animator;
	qCollider* m_Collider;
};

