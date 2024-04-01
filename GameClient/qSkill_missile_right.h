#pragma once
#include "qObj.h"

class qCamera;
class qTexture;
class qAnimator;

class qSkill_missile_right : public qObj
{
	CLONE(qSkill_missile_right);

public:
	qSkill_missile_right();
	qSkill_missile_right(const qSkill_missile_right& _Other);
	~qSkill_missile_right();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }



private:
	qAnimator* m_Animator;
};
