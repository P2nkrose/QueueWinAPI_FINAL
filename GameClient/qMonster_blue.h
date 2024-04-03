#pragma once
#include "qObj.h"

class qTexture;
class qCollider;
class qFSM;
class qAnimator;

class qMonster_blue : public qObj
{
public:

	CLONE(qMonster_blue);

	qMonster_blue(DIRECTION _Dir);
	qMonster_blue(const qMonster_blue& _Other);
	~qMonster_blue();

public:
	virtual void begin() override;
	virtual void tick() override;
	
	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;
	virtual void OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;

private:

	Vec2			m_Pos;

	int				m_BlueHP;
	float			m_Speed;
	float			m_MaxDistance;
	
	DIRECTION		m_Dir;

	qAnimator*		m_Animator;
	qCollider*		m_Collider;
	qRigidbody*		m_Rigidbody;


	qFSM*			m_FSM;

	//Vec2			m_Data;
	//float			m_DetectRange;
};

