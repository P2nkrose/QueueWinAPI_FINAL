#pragma once
#include "qObj.h"

class qCamera;
class qTexture;
class qAnimator;
class qSound;

class qSkill_special_left : public qObj
{
	CLONE(qSkill_special_left);

public:
	qSkill_special_left();
	qSkill_special_left(const qSkill_special_left& _Other);
	~qSkill_special_left();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }
	qCollider* GetCollider() { return m_Collider; }

	virtual void OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;

private:
	qAnimator*		m_Animator;
	qCollider*		m_Collider;
	qSound*			pSound;
};

