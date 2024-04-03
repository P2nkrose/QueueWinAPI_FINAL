#pragma once
#include "qObj.h"

class qSound;
class qAnimator;
class qTexture;



class qEffect_missile : public qObj
{
	CLONE(qEffect_missile);

public:
	qEffect_missile();
	qEffect_missile(const qEffect_missile& _Other);
	~qEffect_missile();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }

	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;

private:
	qAnimator*		m_Animator;
	qSound*			pSound;
};

