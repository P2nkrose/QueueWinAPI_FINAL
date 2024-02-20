#pragma once
#include "qComponent.h"

// vector : ũ��, ����	(�ӵ� : velocity)
// scalar : ũ��			(�ӷ� : speed)

// ������ ���̸� 1�� �ϸ� ���⸸ ������, �׷��� �װ��� normalize (����ȭ) ��� �Ѵ�.


class qRigidbody : public qComponent
{
public:

	CLONE(qRigidbody);

	qRigidbody();
	~qRigidbody();

	virtual void finaltick() override;


public:
	void AddForce(Vec2 _vForce) { m_Force += _vForce; }						// �� �߰�
	void SetMass(float _Mass) { m_Mass = _Mass; }							// ���� ����
	void SetInitialWalkSpeed(float _Speed) { m_InitWalkSpeed = _Speed; }	// �ʱ� �̵��ӵ� ����
	void SetMaxWalkSpeed(float _Speed) { m_MaxWalkSpeed = _Speed; }			// �ִ� �̵��ӵ� ����
	void SetFriction(float _Friction) { m_Friction = _Friction; }

	float GetMass() { return m_Mass; }
	float GetInitWalkSpeed() { return m_InitWalkSpeed; }
	float GetMaxWalkSpeed() { return m_MaxWalkSpeed; }
	float GetFriction() { return m_Friction; }


private:

	Vec2	m_Velocity;			// �ӵ� (����, ũ�������� ���� �ִ�. �׷��� vector �� �θ���.
	float	m_Mass;				// ����
	Vec2	m_Force;			// ��

	float	m_InitWalkSpeed;	// �ʱ� �̵��ӵ�
	float	m_MaxWalkSpeed;		// �ִ� �̵��ӵ�

	float	m_Friction;			// ������
};

