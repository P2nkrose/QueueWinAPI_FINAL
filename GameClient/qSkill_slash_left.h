#pragma once
#include "qObj.h"

class qCamera;
class qTexture;
class qAnimator;
class qSound;

class qSkill_slash_left : public qObj
{
	CLONE(qSkill_slash_left);

public:
	qSkill_slash_left();
	qSkill_slash_left(const qSkill_slash_left& _Other);
	~qSkill_slash_left();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }
	qCollider* GetCollider() { return m_Collider; }

	virtual void OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;

	void SetOwner(qObj* _Owner) { m_Owner = _Owner; }

private:
	qAnimator*		m_Animator;
	qCollider*		m_Collider;
	qObj*			m_Owner;
	qSound*			pSound;
};

