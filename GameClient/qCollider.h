#pragma once
#include "qComponent.h"

class qCollider : public qComponent
{
public:
	friend class qCollisionMgr;

	qCollider();
	~qCollider();


public:
	virtual void finaltick() override;
	virtual qCollider* Clone() { return new qCollider; }
	

public:
	void SetOffsetPos(Vec2 _Offset) { m_OffsetPos = _Offset; }
	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

	Vec2 GetFinalPos() { return m_FinalPos; }
	Vec2 GetScale() { return m_Scale; }

	void SetActive(bool _Set) { m_Active = _Set; }


private:

	void BeginOverlap(qCollider* _OtherCollider);
	void OnOverlap(qCollider* _OtherCollider);
	void EndOverlap(qCollider* _OtherCollider);


private:
	Vec2	m_OffsetPos;		// 소유 오브젝트로부터 상대적인 좌표
	Vec2	m_Scale;

	Vec2	m_FinalPos;			// 최종 좌표 (소유 오브젝트 포지션 + 오프셋 포즈)

	bool	m_Active;
	UINT	m_CollisionCount;	// 카운트를 활용하여 충돌상태를 체크한다.
};

