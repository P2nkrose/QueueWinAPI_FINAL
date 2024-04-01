#pragma once
#include "qObj.h"

class qCamera;
class qTexture;
class qAnimator;

class qSkill_missile_left : public qObj
{
	CLONE(qSkill_missile_left);

public:
	qSkill_missile_left();
	qSkill_missile_left(const qSkill_missile_left& _Other);
	~qSkill_missile_left();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }



private:
	qAnimator* m_Animator;
};
