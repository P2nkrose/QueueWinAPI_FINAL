#pragma once
#include "qObj.h"

class qBossSkill_ball_right : public qObj
{
public:
	CLONE(qBossSkill_ball_right);

	qBossSkill_ball_right();
	~qBossSkill_ball_right();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }
	qCollider* GetCollider() { return m_Collider; }

	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;

private:
	qAnimator* m_Animator;
	qCollider* m_Collider;

	float			m_BallSpeed;
};

