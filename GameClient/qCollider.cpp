#include "pch.h"
#include "qCollider.h"

#include "qLevelMgr.h"
#include "qLevel.h"

qCollider::qCollider()
	: m_Active(true)
	, m_CollisionCount(0)
{
}

qCollider::~qCollider()
{
}

void qCollider::finaltick()
{
	m_FinalPos = GetOwner()->GetPos() + m_OffsetPos;

	if (m_Active)
	{
		// 충돌체를 소유하고 있는 오브젝트의 소속 레이어에 자신을 등록시킨다.
		qLevel* pLevel = qLevelMgr::GetInst()->GetCurrentLevel();
		pLevel->RegisterCollider(this);
	}

	if (0 != m_CollisionCount)
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
	m_CollisionCount++;

	GetOwner()->BeginOverlap(this, _OtherCollider->GetOwner(), _OtherCollider);
}

void qCollider::OnOverlap(qCollider* _OtherCollider)
{
	GetOwner()->OnOverlap(this, _OtherCollider->GetOwner(), _OtherCollider);
}

void qCollider::EndOverlap(qCollider* _OtherCollider)
{
	m_CollisionCount--;

	GetOwner()->EndOverlap(this, _OtherCollider->GetOwner(), _OtherCollider);
}
