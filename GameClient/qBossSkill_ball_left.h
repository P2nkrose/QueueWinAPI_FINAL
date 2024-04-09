#pragma once
#include "qObj.h"

class qCamera;
class qTexture;
class qAnimator;

class qBossSkill_ball_left : public qObj
{
	CLONE(qBossSkill_ball_left);

public:
	qBossSkill_ball_left();
	qBossSkill_ball_left(const qBossSkill_ball_left& _Other);
	~qBossSkill_ball_left();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }
	qCollider* GetCollider() { return m_Collider; }

	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;

private:
	qAnimator*		m_Animator;
	qCollider*		m_Collider;

	float			m_BallSpeed;
};

