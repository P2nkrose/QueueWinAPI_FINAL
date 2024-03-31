#pragma once
#include "qObj.h"

class qTexture;

class qMonster_red : public qObj
{
public:
	CLONE(qMonster_red);

	qMonster_red();
	qMonster_red(Vec2 _Pos, Vec2 _Scale);
	~qMonster_red();


public:
	virtual void begin() override;
	virtual void tick() override;
	virtual void render() override;
	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;


private:

	int			m_HP;
	float		m_DetectRange;
	float		m_Speed;

	//Vec2		m_Data;

	qTexture* m_Img;

	qCollider* m_Collider;
	qRigidbody* m_Rigidbody;
	qFSM* m_FSM;

};

