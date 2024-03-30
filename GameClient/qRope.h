#pragma once
#include "qObj.h"

class qRope : public qObj
{
	CLONE(qRope);

public:
	qRope();
	qRope(Vec2 _Pos, Vec2 _Scale);
	~qRope();

	virtual void tick();
	virtual void render();

	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;
	virtual void OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;
	virtual void EndOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;


private:
	qCollider*		m_Collider;
};

