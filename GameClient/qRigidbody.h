#pragma once
#include "qComponent.h"

// vector : 크기, 방향	
// scalar : 크기			

// 속도 : Velocity
// 속력 : Speed

// 빗변의 길이를 1로 하면 방향만 나오며, 그러면 그것을 normalize (정규화) 라고 한다.


class qRigidbody : public qComponent
{
public:

	CLONE(qRigidbody);

	qRigidbody();
	~qRigidbody();

	virtual void finaltick() override;


public:
	void AddForce(Vec2 _vForce) { m_Force += _vForce; }						// 힘 추가

	void SetMass(float _Mass) { m_Mass = _Mass; }							// 질량 설정
	void SetInitialWalkSpeed(float _Speed) { m_InitWalkSpeed = _Speed; }	// 초기 이동속도 설정
	void SetMaxWalkSpeed(float _Speed) { m_MaxWalkSpeed = _Speed; }			// 최대 이동속도 설정
	void SetMaxGravitySpeed(float _Speed) { m_MaxGravitySpeed = _Speed; }	// 최대 중력가속도 설정
	void SetFriction(float _Friction) { m_Friction = _Friction; }
	void SetJumpSpeed(float _Speed) { m_JumpSpeed = _Speed; }

	void jump();

	float GetMass() { return m_Mass; }
	float GetInitWalkSpeed() { return m_InitWalkSpeed; }
	float GetMaxWalkSpeed() { return m_MaxWalkSpeed; }
	float GetFriction() { return m_Friction; }
	Vec2 GetGravityVelocity() { return m_VelocityByGravity; }

	void UseGravity(bool _Use)
	{
		m_UseGravity = _Use;
		if (!m_UseGravity)
			m_VelocityByGravity = Vec2(0.f, 0.f);
	}

	void SetGround(bool _Ground)
	{
		m_Ground = _Ground;

		if (m_Ground)
			m_VelocityByGravity = Vec2(0.f, 0.f);
	}

	bool IsGround() { return m_Ground; }

private:

	Vec2	m_Velocity;				// 속도 (방향, 크기정보를 갖고 있다. 그래서 vector 라 부른다.
	Vec2	m_VelocityByGravity;	// 중력에 의해서 증가하는 속도
	Vec2	m_AddVelocity;			// 최종 속도에 누적될 속도

	float	m_Mass;					// 질량
	Vec2	m_Force;				// 힘

	float	m_InitWalkSpeed;		// 최소 보장 속력
	float	m_MaxWalkSpeed;			// 최대 제한 속력
	float	m_MaxGravitySpeed;		// 중력으로 발생한 낙하속도 제한

	float	m_Friction;				// 마찰력

	float	m_GravityAccel;			// 중력 가속도
	bool	m_UseGravity;			// 중력 사용 <-> 미사용 bool
	bool	m_Ground;				// 땅 위에 서있는지 체크
	float	m_JumpSpeed;			// 점프 속력


};

