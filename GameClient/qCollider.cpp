#include "pch.h"
#include "qCollider.h"

#include "qLevelMgr.h"
#include "qLevel.h"

qCollider::qCollider()
	: m_Active(true)
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
		// �浹ü�� �����ϰ� �ִ� ������Ʈ�� �Ҽ� ���̾ �ڽ��� ��Ͻ�Ų��.
		qLevel* pLevel = qLevelMgr::GetInst()->GetCurrentLevel();
		pLevel->RegisterCollider(this);
	}

	DrawDebugRect(PEN_TYPE::PEN_GREEN, m_FinalPos, m_Scale, 0.f);
}
