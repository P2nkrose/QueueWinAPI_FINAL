#pragma once
#include "qObj.h"

class qPlatform : public qObj
{
	CLONE(qPlatform)

public:
	qPlatform();
	~qPlatform();

	virtual void tick();

	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;
	virtual void OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;
	virtual void EndOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider) override;

private:
	qCollider* m_Collider;
};

