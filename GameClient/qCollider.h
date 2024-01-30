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
	Vec2	m_OffsetPos;		// ���� ������Ʈ�κ��� ������� ��ǥ
	Vec2	m_Scale;

	Vec2	m_FinalPos;			// ���� ��ǥ (���� ������Ʈ ������ + ������ ����)
};

