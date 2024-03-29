#pragma once
#include "qObj.h"

class qPlatform : public qObj
{
	CLONE(qPlatform)

public:
	qPlatform();
	qPlatform(Vec2 _Pos, Vec2 _Scale, PLATFORM_TYPE _Type);
	~qPlatform();

	virtual void tick();
	virtual void render();

	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;
	virtual void OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;
	virtual void EndOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;

private:
	qCollider*		m_Collider;
	PLATFORM_TYPE   m_eType;
};

