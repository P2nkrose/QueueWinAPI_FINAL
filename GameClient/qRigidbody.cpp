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

	// ���ӵ�
	m_Velocity += vAccel * DT;

	// �ִ�ӵ� ����
	if (0.f != m_MaxWalkSpeed && m_MaxWalkSpeed < m_Velocity.Length())
	{
		m_Velocity.Normalize();
		m_Velocity *= m_MaxWalkSpeed;
	}

	// �ּ� �ӵ� ����
	if (m_InitWalkSpeed != 0.f && m_Velocity.Length() < 10.f && !vAccel.IsZero())
	{
		Vec2 vForceDir = m_Force;
		vForceDir.Normalize();
		m_Velocity = vForceDir * m_InitWalkSpeed;
	}

	// ���� RigidBody �� ����� ���� �����鼭, �ӵ��� �ִ� ���
	// ������ ���ؼ� ���� �ӵ��� ���δ�.

	if (m_Force.IsZero())
	{
		float Speed = m_Velocity.Length();
		Speed -= m_Friction * DT;

		// ������ ���ؼ� �ӵ��� ������ ���� ���� ���� ������,
		// ���ҵ� �ӷ��� ũ�Ⱑ ������ ���� �ʰ� �����Ѵ�.
		if (Speed < 0)
			Speed = 0.f;

		if (!m_Velocity.IsZero())
			m_Velocity.Normalize();

		m_Velocity *= Speed;
	}

	// ���� �ӵ��� ���� �̵�
	// �ӵ� = �Ÿ� / �ð�
	vObjPos += m_Velocity * DT;

	GetOwner()->SetPos(vObjPos);

	// �̹� ������ �� �ʱ�ȭ
	m_Force = Vec2(0.f, 0.f);

	// DebugRender

}
