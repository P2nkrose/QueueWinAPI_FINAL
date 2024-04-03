#pragma once
#include "qObj.h"

class qTexture;
class qCollider;

class qDummy_red : public qObj
{
public:
	CLONE(qDummy_red);

	qDummy_red();
	qDummy_red(const qDummy_red& _Other);
	~qDummy_red();


public:
	virtual void begin() override;
	virtual void tick() override;
	virtual void render() override;


private:
	Vec2			m_Pos;
	qTexture*		m_Img;
	qCollider*		m_Collider;
};

