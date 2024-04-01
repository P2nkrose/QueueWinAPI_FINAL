#pragma once
#include "qObj.h"

class qCamera;
class qTexture;
class qAnimator;

class qSkill_missile_ball_right : public qObj
{
	CLONE(qSkill_missile_ball_right);

public:
	qSkill_missile_ball_right();
	qSkill_missile_ball_right(const qSkill_missile_ball_right& _Other);
	~qSkill_missile_ball_right();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }
	qCollider* GetCollider() { return m_Collider; }

	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;

private:
	qAnimator* m_Animator;
	qCollider* m_Collider;
};

