#include "pch.h"
#include "qPlatform.h"

#include "qCollider.h"
#include "qRigidbody.h"

qPlatform::qPlatform()
	: m_Collider(nullptr)
{
	SetScale(Vec2(500.f, 100.f));
	m_Collider = (qCollider*)AddComponent(new qCollider);
	m_Collider->SetScale(GetScale());
}

qPlatform::~qPlatform()
{
}

void qPlatform::tick()
{
}

void qPlatform::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	if (_OtherObj->GetName() == L"Player")
	{
		qRigidbody* pRB = _OtherObj->GetComponent<qRigidbody>();
		pRB->SetGround(true);
	}
}

void qPlatform::OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
}

void qPlatform::EndOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	if (_OtherObj->GetName() == L"Player")
	{
		qRigidbody* pRB = _OtherObj->GetComponent<qRigidbody>();
		pRB->SetGround(false);
	}
}
