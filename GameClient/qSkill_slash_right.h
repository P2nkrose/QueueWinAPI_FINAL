#pragma once
#include "qObj.h"

class qCamera;
class qTexture;
class qAnimator;

class qSkill_slash_right : public qObj
{
	CLONE(qSkill_slash_right);

public:
	qSkill_slash_right();
	qSkill_slash_right(const qSkill_slash_right& _Other);
	~qSkill_slash_right();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }
	qCollider* GetCollider() { return m_Collider; }

	void SetOwner(qObj* _Owner) { m_Owner = _Owner; }

	virtual void OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;


private:
	qAnimator*		m_Animator;
	qCollider*		m_Collider;
	qObj*			m_Owner;
};

