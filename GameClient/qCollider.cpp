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
		// 충돌체를 소유하고 있는 오브젝트의 소속 레이어에 자신을 등록시킨다.
		qLevel* pLevel = qLevelMgr::GetInst()->GetCurrentLevel();
		pLevel->RegisterCollider(this);

		// 비활성화 상태면 등록옵션을 정지한다. (다음번 프레임부터 등록이 되지 않는다.)
		if (!m_Active)
		{
			m_bRegister = false;
		}

	}

	// 비활성화 상태의 충돌체는 DebugRender 를 요청하지 않는다.
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
