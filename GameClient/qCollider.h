#pragma once
#include "qComponent.h"

class qCollider : public qComponent
{
public:
	qCollider();
	~qCollider();


public:
	virtual void finaltick() override;
	virtual qCollider* Clone() { return new qCollider; }
	

public:
	void SetOffsetPos(Vec2 _Offset) { m_OffsetPos = _Offset; }
	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }



private:
	Vec2	m_OffsetPos;		// 소유 오브젝트로부터 상대적인 좌표
	Vec2	m_Scale;

	Vec2	m_FinalPos;			// 최종 좌표 (소유 오브젝트 포지션 + 오프셋 포즈)
};

