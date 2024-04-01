#pragma once
#include "qObj.h"

class qCamera;
class qTexture;
class qAnimator;

class qSkill_missile_ball_left : public qObj
{
	CLONE(qSkill_missile_ball_left);

public:
public:
	qSkill_missile_ball_left();
	qSkill_missile_ball_left(const qSkill_missile_ball_left& _Other);
	~qSkill_missile_ball_left();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }
	qCollider* GetCollider() { return m_Collider; }

	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;

private:
	qAnimator* m_Animator;
	qCollider* m_Collider;

	float	   m_BallSpeed;
};

