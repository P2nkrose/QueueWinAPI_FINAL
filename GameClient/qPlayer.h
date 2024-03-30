#pragma once
#include "qObj.h"

class qCollider;
class qAnimator;
class qRigidbody;
class qFSM;


class qPlayer : public qObj
{
private:
	PLAYER_STATE		m_State;
	

	float			m_Speed;
	float			m_Hud;
	float			m_SlashSpeed;
	float			m_SlashRange;
	bool			m_Slash;

	bool			m_Portal;		// Æ÷Å»

	LEVEL_TYPE		m_Level;

	Vec2			m_Pos;

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

