#pragma once
#include "qObj.h"

class qTexture;
class qCollider;
class qFSM;
class qAnimator;


class qBoss : public qObj
{
public:

	CLONE(qBoss);

	qBoss();
	qBoss(const qBoss& _Other);
	~qBoss();

public:
	virtual void begin() override;
	virtual void tick() override;

	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;
	virtual void OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;



private:

	int				m_BossHP;
	DIRECTION		m_Dir;
	
	qAnimator*		m_Animator;
	qCollider*		m_Collider;
	qRigidbody*		m_Rigidbody;
	qFSM*			m_FSM;



};

