#include "pch.h"
#include "qRope.h"

#include "qCollider.h"
#include "qRigidbody.h"
#include "qPlayer.h"

#include "qKeyMgr.h"
#include "qLevelMgr.h"
#include "qLevel.h"

qRope::qRope()
	: m_Collider(nullptr)
{
}

qRope::qRope(Vec2 _Pos, Vec2 _Scale)
	: m_Collider(nullptr)

{
	SetPos(_Pos);
	SetScale(_Scale);
	m_Collider = (qCollider*)AddComponent(new qCollider);
	m_Collider->SetScale(GetScale());
}

qRope::~qRope()
{
}

void qRope::tick()
{
	qObj::tick();
}

void qRope::render()
{
	qObj::render();
}

void qRope::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	if (_OtherObj->GetName() == L"Player")
	{
		qPlayer* pPlayer = static_cast<qPlayer*>(_OtherObj);
		pPlayer->SetRope(true);
		pPlayer->SetTargetRope(this);	

	}
}

void qRope::OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
}

void qRope::EndOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	if (_OtherObj->GetName() == L"Player")
	{
		qRigidbody* pRB = _OtherObj->GetComponent<qRigidbody>();
		pRB->SetRope(false);
		static_cast<qPlayer*>(_OtherObj)->SetRope(false);
	}
}
