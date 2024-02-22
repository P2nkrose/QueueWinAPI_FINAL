#pragma once
#include "qObj.h"

class qCollider;
class qAnimator;
class qRigidbody;

class qPlayer : public qObj
{
private:
	float		m_Speed;

	qTexture*	m_PlayerImg;

	qCollider*	m_HeadCol;
	qCollider*	m_BodyCol;
	qAnimator*	m_Animator;
	qRigidbody* m_RigidBody;


	int			m_DoubleJumpCount;
	int			m_CurJumpCount;

public:
	virtual void begin();
	virtual void tick();	

	void Shoot();
	void Jump();

	void RestoreJumpCount()
	{
		m_CurJumpCount = 0;
	}


	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;
	virtual void OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;
	virtual void EndOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;


public:
	virtual qObj* Clone() override { return new qPlayer(*this); };



public:
	qPlayer();
	~qPlayer();

};

