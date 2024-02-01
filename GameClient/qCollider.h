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
	Vec2	m_OffsetPos;		// ���� ������Ʈ�κ��� ������� ��ǥ
	Vec2	m_Scale;

	Vec2	m_FinalPos;			// ���� ��ǥ (���� ������Ʈ ������ + ������ ����)

	bool	m_Active;
	UINT	m_CollisionCount;	// ī��Ʈ�� Ȱ���Ͽ� �浹���¸� üũ�Ѵ�.
};

