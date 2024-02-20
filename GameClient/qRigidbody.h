#pragma once
#include "qComponent.h"

// vector : 크기, 방향	(속도 : velocity)
// scalar : 크기			(속력 : speed)

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
	void SetFriction(float _Friction) { m_Friction = _Friction; }

	float GetMass() { return m_Mass; }
	float GetInitWalkSpeed() { return m_InitWalkSpeed; }
	float GetMaxWalkSpeed() { return m_MaxWalkSpeed; }
	float GetFriction() { return m_Friction; }


private:

	Vec2	m_Velocity;			// 속도 (방향, 크기정보를 갖고 있다. 그래서 vector 라 부른다.
	float	m_Mass;				// 질량
	Vec2	m_Force;			// 힘

	float	m_InitWalkSpeed;	// 초기 이동속도
	float	m_MaxWalkSpeed;		// 최대 이동속도

	float	m_Friction;			// 마찰력
};

