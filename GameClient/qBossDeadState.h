#pragma once
#include "qState.h"

class qBossDeadState : public qState
{
public:
	CLONE(qBossDeadState);
	
	qBossDeadState();
	~qBossDeadState();

public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

	void SetDir(float _Dir) { m_Dir = _Dir; }
	float GetDir() { return m_Dir; }


private:
	Vec2		m_Pos;
	Vec2		m_CenterPos;
	float		m_Time;
	float		m_Dir;
};

