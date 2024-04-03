#pragma once
#include "qObj.h"

class qCollider;
class qTexture;

class qMonster_red : public qObj
{
public:
	CLONE(qMonster_red);

	qMonster_red(DIRECTION _Dir);
	qMonster_red(const qMonster_red& _Other);
	~qMonster_red();


public:
	virtual void begin() override;
	virtual void tick() override;
	
	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;
	virtual void OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;

private:

	Vec2		m_Pos;
	int			m_RedHP;
	float		m_Speed;

	float		m_MaxDistance;

	DIRECTION	m_Dir;

	qAnimator*	m_Animator;
	qCollider*	m_Collider;
	qRigidbody* m_Rigidbody;

	qFSM* m_FSM;

};

