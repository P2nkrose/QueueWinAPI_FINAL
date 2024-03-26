#pragma once
#include "qState.h"

class qAnimator;
class qTexture;
class qRigidbody;
class qCollider;

class qPlayerState : public qState
{
public:
	CLONE(qPlayerState);

public:
	qPlayerState();
	~qPlayerState();

public:
	virtual void Enter() override;
	virtual void FinalTick() override;
	virtual void Exit() override;


	void RestoreJumpCount()
	{
		m_CurJumpCount = 0;
	}


public:
	void Idle();
	void Move();
	void Down();
	void DownAttack();
	void Buff();
	void Attack();
	void Missile();
	void Slash();
	void Special();
	void Jump();
	void Rope();


private:
	void SetState(PLAYER_STATE _State) { m_State = _State; }
	PLAYER_STATE GetState() { return m_State; }

	void SetDirection(DIRECTION _Dir) { m_Dir = _Dir; }
	DIRECTION GetDirection() { return m_Dir; }

private:
	PLAYER_STATE		m_State;
	DIRECTION	m_Dir;

	qTexture*			m_PlayerImg;
	qAnimator*			m_Animator;
	qRigidbody*			m_RigidBody;
	qCollider*			m_Collider;


	int					m_DoubleJumpCount;
	int					m_CurJumpCount;


private:
	qObj*				m_Player;
	Vec2				m_Pos;

	float				m_Speed;
	float				m_Hud;
	bool				m_Jump;
};		  
