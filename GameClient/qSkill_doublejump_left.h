#pragma once
#include "qObj.h"

class qCamera;
class qTexture;
class qAnimator;
class qSound;

class qSkill_doublejump_left : public qObj
{
	CLONE(qSkill_doublejump_left);

public:
	qSkill_doublejump_left();
	qSkill_doublejump_left(const qSkill_doublejump_left& _Other);
	~qSkill_doublejump_left();

	virtual void tick() override;

	qAnimator* GetAnimator() { return m_Animator; }

	

private:
	qAnimator*		m_Animator;
	qSound*			pSound;
};

