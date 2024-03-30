#include "pch.h"
#include "qPortal.h"

#include "qCollider.h"
#include "qPlayer.h"

#include "qLevelMgr.h"
#include "qLevel.h"

qPortal::qPortal()
	: m_Collider(nullptr)
{
}

qPortal::qPortal(Vec2 _Pos, Vec2 _Scale)
	: m_Collider(nullptr)
{
	SetPos(_Pos);
	SetScale(_Scale);
	m_Collider = (qCollider*)AddComponent(new qCollider);
	m_Collider->SetScale(GetScale());
}

qPortal::~qPortal()
{
}

void qPortal::tick()
{
	qObj::tick();
}

void qPortal::render()
{
	qObj::render();
}

void qPortal::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{

}

void qPortal::OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	if (_OtherObj->GetName() == L"Player")
	{
		dynamic_cast<qPlayer*>(_OtherObj)->SetPortal(true);
	}
}

void qPortal::EndOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	if (_OtherObj->GetName() == L"Player")
	{
		dynamic_cast<qPlayer*>(_OtherObj)->SetPortal(false);
	}
}
