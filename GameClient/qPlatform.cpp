#include "pch.h"
#include "qPlatform.h"

#include "qCollider.h"
#include "qRigidbody.h"

qPlatform::qPlatform()
	: m_Collider(nullptr)
{
	//SetScale(Vec2(500.f, 100.f));
	//m_Collider = (qCollider*)AddComponent(new qCollider);
	//m_Collider->SetScale(GetScale());
}

qPlatform::qPlatform(Vec2 _Pos, Vec2 _Scale)
	: m_Collider(nullptr)
{
	SetPos(_Pos);
	SetScale(_Scale);
	m_Collider = (qCollider*)AddComponent(new qCollider);
	m_Collider->SetScale(GetScale());
}



qPlatform::~qPlatform()
{
}

void qPlatform::tick()
{
}

void qPlatform::render()
{
	if (L"Test" == GetName())
	{
		USE_PEN(DC, PEN_TYPE::PEN_GREEN);
		USE_BRUSH(DC, BRUSH_TYPE::BRUSH_HOLLOW);

		Vec2 vPos = qCamera::GetInst()->GetRenderPos(GetPos());
		Vec2 vScale = qCamera::GetInst()->GetRealPos(GetScale());

		Rectangle(DC, (int)vPos.x, (int)vPos.y, (int)vScale.x, (int)vScale.y);
	}
	else
	{
		return;
	}
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
