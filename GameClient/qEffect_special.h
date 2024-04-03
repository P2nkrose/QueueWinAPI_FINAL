#pragma once
#include "qObj.h"

class qSound;
class qAnimator;
class qTexture;

class qEffect_special : public qObj
{
public:

	CLONE(qEffect_special);

	qEffect_special();
	qEffect_special(const qEffect_special& _Other);
	~qEffect_special();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }

	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;

private:
	qAnimator* m_Animator;
	qSound* pSound;

};

