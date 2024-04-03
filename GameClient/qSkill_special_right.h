#pragma once
#include "qObj.h"

class qCamera;
class qTexture;
class qAnimator;
class qSound;

class qSkill_special_right : public qObj
{
	CLONE(qSkill_special_right);

public:
	qSkill_special_right();
	qSkill_special_right(const qSkill_special_right& _Other);
	~qSkill_special_right();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }
	qCollider* GetCollider() { return m_Collider; }

	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;

private:
	qAnimator*		m_Animator;
	qCollider*		m_Collider;
	qSound*			pSound;
};

