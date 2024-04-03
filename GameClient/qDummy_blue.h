#pragma once
#include "qObj.h"

class qTexture;
class qCollider;

class qDummy_blue : public qObj
{
public:
	CLONE(qDummy_blue);

	qDummy_blue();
	qDummy_blue(const qDummy_blue& _Other);
	~qDummy_blue();


public:
	virtual void begin() override;
	virtual void tick() override;
	virtual void render() override;


private:
	Vec2			m_Pos;
	qTexture*		m_Img;
	qCollider*		m_Collider;
};

