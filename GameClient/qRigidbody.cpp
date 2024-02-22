#include "pch.h"
#include "qRigidbody.h"

qRigidbody::qRigidbody()
	: m_Mass(1.f)
	, m_InitWalkSpeed(0.f)
	, m_MaxWalkSpeed(0.f)
	, m_MaxGravitySpeed(0.f)
	, m_Friction(500.f)
	, m_GravityAccel(980.f)
	, m_UseGravity(false)
	, m_JumpSpeed(400.f)
	, m_GroundFunc(nullptr)
	, m_AirFunc(nullptr)
	, m_GroundInst(nullptr)
	, m_AirInst(nullptr)
	, m_GroundDelegate(nullptr)
	, m_AirDelegate(nullptr)
{
}

qRigidbody::~qRigidbody()
{
}

void qRigidbody::jump()
{
	m_VelocityByGravity += Vec2(0.f, -1.f) * m_JumpSpeed;
	SetGround(false);
}


void qRigidbody::finaltick()
{
	Vec2 vObjPos = GetOwner()->GetPos();

	// F = M x A
	Vec2 vAccel = m_Force / m_Mass;

	// 가속도
	// 중력을 사용할 때, 공중에서 힘이 적용된 경우
	if (m_UseGravity && !m_Ground)
	{
		m_Velocity += vAccel * DT * 0.5f;
	}
	else
	{
		m_Velocity += vAccel * DT * 1.f;
	}

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
		

		// 중력 기능을 켰고, 공중 상태인 경우
		if (m_UseGravity && !m_Ground)
		{
			// 마찰을 더 적게 적용한다.
			Speed -= m_Friction * DT * 0.2f;
		}
		else
		{
			Speed -= m_Friction * DT;
		}

		// 마찰에 의해서 속도가 역으로 생길 수는 없기 때문에,
		// 감소된 속력의 크기가 음수가 되지 않게 보정한다.
		if (Speed < 0)
			Speed = 0.f;

		if (!m_Velocity.IsZero())
			m_Velocity.Normalize();

		m_Velocity *= Speed;
	}


	// 중력 가속도에 의한 속도 증가
	if (m_UseGravity && !m_Ground)
	{
		m_VelocityByGravity += Vec2(0.0f, 1.f) * m_GravityAccel * DT;

		if (0.f != m_MaxGravitySpeed && m_MaxGravitySpeed < m_VelocityByGravity.Length())
		{
			m_VelocityByGravity.Normalize();
			m_VelocityByGravity *= m_MaxGravitySpeed;
		}
	}

	// 최종 속도
	Vec2 vFinalVelocity = m_Velocity + m_VelocityByGravity;


	// 현재 속도에 따른 이동
	// 속도 = 거리 / 시간
	vObjPos += vFinalVelocity * DT;
	GetOwner()->SetPos(vObjPos);

	// 이번 프레임 힘 초기화
	m_Force = Vec2(0.f, 0.f);
	m_AddVelocity = Vec2(0.f, 0.f);

	// DebugRender
	DrawDebugLine(PEN_TYPE::PEN_BLUE, vObjPos, vObjPos + vFinalVelocity, 0.f);

}

