#pragma once
#include "qObj.h"

class qCamera;
class qTexture;
class qAnimator;
class qSound;

class qSkill_doublejump_right : public qObj
{
	CLONE(qSkill_doublejump_right);

public:
	qSkill_doublejump_right();
	qSkill_doublejump_right(const qSkill_doublejump_right& _Other);
	~qSkill_doublejump_right();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }



private:
	qAnimator*		m_Animator;
	qSound*			pSound;
};

