#pragma once
#include "qObj.h"

class qCollider;
class qAnimator;
class qRigidbody;
class qFSM;
class qRope;

class qPlayer : public qObj
{
private:
	PLAYER_STATE		m_State;
	

	float			m_Speed;
	float			m_Hud;
	float			m_SlashSpeed;
	float			m_SlashMaxRange;
	bool			m_Slash;

	bool			m_Portal;		// Æ÷Å»
	bool			m_bRope;
	qRope*			m_Rope;

	LEVEL_TYPE		m_Level;

	Vec2			m_Pos;
	Vec2			m_CenterPos;

	qTexture*		m_PlayerImg;

	qCollider*		m_HeadCol;
	qCollider*		m_BodyCol;
	qAnimator*		m_Animator;
	qRigidbody*		m_RigidBody;
	qFSM*			m_FSM;

	int				m_DoubleJumpCount;
	int				m_CurJumpCount;

public:
	virtual void begin();
	virtual void tick();	


	//void Shoot();
	void Jump();
	void DoubleJump();
	void RestoreJumpCount()
	{
		m_CurJumpCount = 0;
	}


	void SetTargetRope(qRope* _Rope) { m_Rope = _Rope; }


	bool IsPortal() { return m_Portal; }
	void SetPortal(bool _Portal)
	{
		m_Portal = _Portal;
	}

	LEVEL_TYPE GetLevel() { return m_Level; }
	void SetLevel(LEVEL_TYPE _Level)
	{
		m_Level = _Level;
	}

	void SetRope(bool _Rope) { m_bRope = _Rope; }

	PLAYER_STATE GetState() { return m_State; }
	void SetState(PLAYER_STATE _State) { m_State = _State; }


	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;
	virtual void OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;
	virtual void EndOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;


public:
	CLONE(qPlayer);

public:
	qPlayer();
	qPlayer(const qPlayer& _Other);
	~qPlayer();

	friend class qRigidbody;
};

