#pragma once
#include "qObj.h"

class qCollider;

class qPlayer : public qObj
{
private:
	float		m_Speed;

	qTexture*	m_PlayerImg;

	qCollider*	m_HeadCol;
	qCollider*	m_BodyCol;

public:
	virtual void begin();
	virtual void tick();		
	virtual void render();


	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;
	virtual void OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;
	virtual void EndOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;


public:
	virtual qObj* Clone() override { return new qPlayer(*this); };


public:
	qPlayer();
	~qPlayer();

};

