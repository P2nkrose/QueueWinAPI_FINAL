#include "pch.h"
#include "qRigidbody.h"

qRigidbody::qRigidbody()
	: m_Mass(1.f)
	, m_InitWalkSpeed(0.f)
	, m_MaxWalkSpeed(0.f)
{
}

qRigidbody::~qRigidbody()
{
}

void qRigidbody::finaltick()
{
	Vec2 vObjPos = GetOwner()->GetPos();

	// F = M x A
	Vec2 vAccel = m_Force / m_Mass;

	// 가속도
	m_Velocity += vAccel * DT;

	// 최대속도 제한
	if (0.f != m_MaxWalkSpeed && m_MaxWalkSpeed < m_Velocity.Length())
	{
		m_Velocity.Normalize();
		m_Velocity *= m_MaxWalkSpeed;
	}

	// 속도 = 거리 / 시간
	vObjPos += m_Velocity * DT;

	GetOwner()->SetPos(vObjPos);

	m_Force = Vec2(0.f, 0.f);

	// DebufRender

}
