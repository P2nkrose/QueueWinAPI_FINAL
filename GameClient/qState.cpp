#include "pch.h"
#include "qState.h"

qState::qState()
	: m_Owner(nullptr)
{
}

qState::~qState()
{
}

void qState::init()
{
	if (nullptr == m_Animator || nullptr == m_Rigidbody || nullptr == m_Collider)
	{
		m_Animator = GetObj()->GetComponent<qAnimator>();
		m_Rigidbody = GetObj()->GetComponent<qRigidbody>();
		m_Collider = GetObj()->GetComponent<qCollider>();
	}

}
