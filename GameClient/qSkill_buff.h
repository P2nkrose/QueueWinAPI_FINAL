#pragma once
#include "qObj.h"

class qCamera;
class qTexture;
class qAnimator;
class qSound;

class qSkill_buff : public qObj
{
	CLONE(qSkill_buff);

public:
	qSkill_buff();
	qSkill_buff(const qSkill_buff& _Other);
	~qSkill_buff();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }



private:
	qAnimator*		m_Animator;
	qSound*			pSound;
};

