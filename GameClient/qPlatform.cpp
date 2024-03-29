#include "pch.h"
#include "qPlatform.h"

#include "qCollider.h"
#include "qRigidbody.h"

#include "qLevelMgr.h"
#include "qLevel.h"

qPlatform::qPlatform()
	: m_Collider(nullptr)
	, m_eType(PLATFORM_TYPE::END)
{
	//SetScale(Vec2(500.f, 100.f));
	//m_Collider = (qCollider*)AddComponent(new qCollider);
	//m_Collider->SetScale(GetScale());
}

qPlatform::qPlatform(Vec2 _Pos, Vec2 _Scale, PLATFORM_TYPE _Type)
	: m_Collider(nullptr)
	, m_eType(_Type)
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
	qObj::tick();
	
	//wchar_t szBuff[256] = {};
	//static float AccTime = 0.f;
	//AccTime += DT;
	//swprintf_s(szBuff, L"x : %f, y : %f", m_Collider->GetFinalPos().x, m_Collider->GetFinalPos().y);

	//if (AccTime >= 1.f)
	//{
	//	LOG(LOG_TYPE::DBG_ERROR, szBuff);
	//	AccTime = 0.f;
	//}
}

void qPlatform::render()
{
	qObj::render();
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

	if (PLATFORM_TYPE::GROUND == m_eType)
	{
		if (_OtherObj->GetName() == L"Player")
		{
			qRigidbody* pRB = _OtherObj->GetComponent<qRigidbody>();
			pRB->SetGround(true);
		}
	}

}

void qPlatform::OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	if (PLATFORM_TYPE::ROPE == m_eType)
	{
		if (_OtherObj->GetName() == L"Player")
		{
			qRigidbody* pRB = _OtherObj->GetComponent<qRigidbody>();
			pRB->SetRope(true);
		}
	}
}

void qPlatform::EndOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	if (PLATFORM_TYPE::GROUND == m_eType)
	{
		if (_OtherObj->GetName() == L"Player")
		{
			qRigidbody* pRB = _OtherObj->GetComponent<qRigidbody>();
			pRB->SetGround(false);
		}
	}
	else if (PLATFORM_TYPE::ROPE == m_eType)
	{
		if (_OtherObj->GetName() == L"Player")
		{
			qRigidbody* pRB = _OtherObj->GetComponent<qRigidbody>();
			pRB->SetRope(false);
		}
	}
	
}
