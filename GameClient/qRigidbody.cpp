#include "pch.h"
#include "qRigidbody.h"

qRigidbody::qRigidbody()
	: m_Mass(1.f)
	, m_InitWalkSpeed(0.f)
	, m_MaxWalkSpeed(0.f)
	, m_Friction(500.f)
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

	// 최소 속도 보정
	if (m_InitWalkSpeed != 0.f && m_Velocity.Length() < 10.f && !vAccel.IsZero())
	{
		Vec2 vForceDir = m_Force;
		vForceDir.Normalize();
		m_Velocity = vForceDir * m_InitWalkSpeed;
	}

	// 만약 RigidBody 에 적용된 힘이 없으면서, 속도는 있는 경우
	// 마찰에 의해서 현재 속도를 줄인다.

	if (m_Force.IsZero())
	{
		float Speed = m_Velocity.Length();
		Speed -= m_Friction * DT;

		// 마찰에 의해서 속도가 역으로 생길 수는 없기 때문에,
		// 감소된 속력의 크기가 음수가 되지 않게 보정한다.
		if (Speed < 0)
			Speed = 0.f;

		if (!m_Velocity.IsZero())
			m_Velocity.Normalize();

		m_Velocity *= Speed;
	}

	// 현재 속도에 따른 이동
	// 속도 = 거리 / 시간
	vObjPos += m_Velocity * DT;

	GetOwner()->SetPos(vObjPos);

	// 이번 프레임 힘 초기화
	m_Force = Vec2(0.f, 0.f);

	// DebugRender

}
