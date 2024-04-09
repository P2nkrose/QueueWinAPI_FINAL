#pragma once
#include "qObj.h"

class qCamera;
class qTexture;
class qAnimator;

class qBossSkill_tornado : public qObj
{
	CLONE(qBossSkill_tornado);

public:
	qBossSkill_tornado();
	~qBossSkill_tornado();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }
	qCollider* GetCollider() { return m_Collider; }

	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;

private:
	qAnimator* m_Animator;
	qCollider* m_Collider;

};

