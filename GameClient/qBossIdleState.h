#pragma once
#include "qState.h"

class qBossIdleState : public qState
{
public:

	CLONE(qBossIdleState);

	qBossIdleState();
	~qBossIdleState();

public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;

	void SetDir(float _Dir) { m_Dir = _Dir; }
	float GetDir() { return m_Dir; }

private:
	Vec2		m_Pos;
	float		m_Time;
	Vec2		m_CenterPos;
	float		m_Dir;
};

