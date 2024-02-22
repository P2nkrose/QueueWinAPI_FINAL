#pragma once
#include "qComponent.h"

typedef void(*CALL_BACK)(void);
typedef void(qObj::*DELEGATE)(void);

// vector : ũ��, ����	
// scalar : ũ��			

// �ӵ� : Velocity
// �ӷ� : Speed

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
	void SetMaxGravitySpeed(float _Speed) { m_MaxGravitySpeed = _Speed; }	// �ִ� �߷°��ӵ� ����
	void SetFriction(float _Friction) { m_Friction = _Friction; }
	void SetJumpSpeed(float _Speed) { m_JumpSpeed = _Speed; }

	void jump();

	float GetMass() { return m_Mass; }
	float GetInitWalkSpeed() { return m_InitWalkSpeed; }
	float GetMaxWalkSpeed() { return m_MaxWalkSpeed; }
	float GetFriction() { return m_Friction; }
	Vec2 GetGravityVelocity() { return m_VelocityByGravity; }

	void SetGroundFunc(void(*_pFunc)(void)) { m_GroundFunc = _pFunc; }
	void SetAirFunc(void(*_pFunc)(void)) { m_AirFunc = _pFunc; }

	void SetGroundDelegate(qObj* _Inst, DELEGATE _MemFunc)
	{
		m_GroundInst = _Inst;
		m_GroundDelegate = _MemFunc;
	}

	void SetAirDelegate(qObj* _Inst, DELEGATE _MemFunc)
	{
		m_AirInst = _Inst;
		m_AirDelegate = _MemFunc;
	}

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
		{
			m_VelocityByGravity = Vec2(0.f, 0.f);

			if (nullptr != m_GroundFunc)
				m_GroundFunc();

			if (m_GroundInst && m_GroundDelegate)
				(m_GroundInst->*m_GroundDelegate)();
		}
		else
		{
			if (nullptr != m_AirFunc)
				m_AirFunc();

			if (m_AirInst && m_AirDelegate)
				(m_AirInst->*m_AirDelegate)();
		}
	}

	bool IsGround() { return m_Ground; }

private:

	Vec2	m_Velocity;				// �ӵ� (����, ũ�������� ���� �ִ�. �׷��� vector �� �θ���.
	Vec2	m_VelocityByGravity;	// �߷¿� ���ؼ� �����ϴ� �ӵ�
	Vec2	m_AddVelocity;			// ���� �ӵ��� ������ �ӵ�

	float	m_Mass;					// ����
	Vec2	m_Force;				// ��

	float	m_InitWalkSpeed;		// �ּ� ���� �ӷ�
	float	m_MaxWalkSpeed;			// �ִ� ���� �ӷ�
	float	m_MaxGravitySpeed;		// �߷����� �߻��� ���ϼӵ� ����

	float	m_Friction;				// ������

	float	m_GravityAccel;			// �߷� ���ӵ�
	bool	m_UseGravity;			// �߷� ��� <-> �̻�� bool
	bool	m_Ground;				// �� ���� ���ִ��� üũ
	float	m_JumpSpeed;			// ���� �ӷ�

	// Ground On / Off ȣ���ų �Լ�������
	CALL_BACK	m_GroundFunc;
	CALL_BACK	m_AirFunc;

	// Delegate
	qObj*		m_GroundInst;
	DELEGATE	m_GroundDelegate;

	qObj*		m_AirInst;
	DELEGATE	m_AirDelegate;

};

