#pragma once
#include "qObj.h"

class qCamera;
class qTexture;
class qAnimator;
class qSound;

class qSkill_highjump : public qObj
{
	CLONE(qSkill_highjump);

public:
	qSkill_highjump();
	qSkill_highjump(const qSkill_highjump& _Other);
	~qSkill_highjump();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }



private:
	qAnimator*		m_Animator;
	qSound*			pSound;
};

