#pragma once
#include "qObj.h"

class qSound;
class qAnimator;
class qTexture;


class qEffect_slash : public qObj
{
	CLONE(qEffect_slash);

public:
	qEffect_slash();
	qEffect_slash(const qEffect_slash& _Other);
	~qEffect_slash();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }

	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;

private:
	qAnimator* m_Animator;
	qSound* pSound;

};

