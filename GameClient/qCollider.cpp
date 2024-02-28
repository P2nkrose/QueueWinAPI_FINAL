#include "pch.h"
#include "qCollider.h"

#include "qLevelMgr.h"
#include "qLevel.h"

qCollider::qCollider()
	: m_Active(true)
	, m_OverlapCount(0)
	, m_bRegister(true)
{
}

qCollider::qCollider(const qCollider& _Other)
	: qComponent(_Other)
	, m_OffsetPos(_Other.m_OffsetPos)
	, m_Scale(_Other.m_Scale)
	, m_OverlapCount(0)
	, m_Active(_Other.m_Active)
	, m_bRegister(_Other.m_bRegister)
{
}

qCollider::~qCollider()
{
}

void qCollider::finaltick()
{
	m_FinalPos = GetOwner()->GetPos() + m_OffsetPos;

	if (m_bRegister)
	{
		// �浹ü�� �����ϰ� �ִ� ������Ʈ�� �Ҽ� ���̾ �ڽ��� ��Ͻ�Ų��.
		qLevel* pLevel = qLevelMgr::GetInst()->GetCurrentLevel();
		pLevel->RegisterCollider(this);

		// ��Ȱ��ȭ ���¸� ��Ͽɼ��� �����Ѵ�. (������ �����Ӻ��� ����� ���� �ʴ´�.)
		if (!m_Active)
		{
			m_bRegister = false;
		}

	}

	// ��Ȱ��ȭ ������ �浹ü�� DebugRender �� ��û���� �ʴ´�.
	if (!m_Active)
	{
		return;
	}

	if (0 != m_OverlapCount)
	{
		DrawDebugRect(PEN_TYPE::PEN_RED, m_FinalPos, m_Scale, 0.f);
	}
	else
	{
		DrawDebugRect(PEN_TYPE::PEN_GREEN, m_FinalPos, m_Scale, 0.f);
	}

}


void qCollider::BeginOverlap(qCollider* _OtherCollider)
{
	m_OverlapCount++;

	GetOwner()->BeginOverlap(this, _OtherCollider->GetOwner(), _OtherCollider);
}

void qCollider::OnOverlap(qCollider* _OtherCollider)
{
	GetOwner()->OnOverlap(this, _OtherCollider->GetOwner(), _OtherCollider);
}

void qCollider::EndOverlap(qCollider* _OtherCollider)
{
	m_OverlapCount--;

	GetOwner()->EndOverlap(this, _OtherCollider->GetOwner(), _OtherCollider);
}
