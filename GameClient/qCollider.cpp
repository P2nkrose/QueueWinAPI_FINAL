#include "pch.h"
#include "qCollider.h"

qCollider::qCollider()
{
}

qCollider::~qCollider()
{
}

void qCollider::finaltick()
{
	m_FinalPos = GetOwner()->GetPos() + m_OffsetPos;

	DrawDebugRect(PEN_TYPE::PEN_GREEN, m_FinalPos, m_Scale, 0.f);
}
