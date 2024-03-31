#include "pch.h"
#include "qMonster_blue.h"

#include "qCollider.h"
#include "qMissile.h"

#include "qRigidbody.h"
#include "qFSM.h"
#include "qIdleState.h"
#include "qTraceState.h"

#include "qLevelMgr.h"

qMonster_blue::qMonster_blue()
	: m_HP(5)
	, m_DetectRange(400)
	, m_Speed(100)
{
	m_Collider = (qCollider*)AddComponent(new qCollider);
	m_Collider->SetScale(Vec2(65.f, 85.f));
	//
	//m_Rigidbody = (qRigidbody*)AddComponent(new qRigidbody);
	//m_Rigidbody->SetMass(2.f);
	//m_Rigidbody->SetInitialWalkSpeed(0.f);
	//m_Rigidbody->SetMaxWalkSpeed(400.f);
	//m_Rigidbody->SetFriction(2000.f);
	//
	m_Img = qAssetMgr::GetInst()->LoadTexture(L"monster_blue", L"texture\\edit\\monster_blue.png");
	//
	//m_FSM = (qFSM*)AddComponent(new qFSM);
	//m_FSM->AddState(L"Idle", new qIdleState);
	//m_FSM->AddState(L"Trace", new qTraceState);
}

qMonster_blue::qMonster_blue(Vec2 _Pos, Vec2 _Scale)
	: m_HP(5)
	, m_DetectRange(400)
	, m_Speed(100)
{
	SetPos(_Pos);
	SetScale(_Scale);
	m_Collider = (qCollider*)AddComponent(new qCollider);
	m_Collider->SetScale(GetScale());
}

qMonster_blue::~qMonster_blue()
{
	
}

void qMonster_blue::begin()
{
	// ���Ͱ� �÷��̾� ã��
	//m_FSM->SetBlackboardData(L"DetectRange", DATA_TYPE::FLOAT, &m_DetectRange);
	//m_FSM->SetBlackboardData(L"Speed", DATA_TYPE::FLOAT, &m_Speed);
	//m_FSM->SetBlackboardData(L"Self", DATA_TYPE::OBJECT, this);
	//
	//qObj* pPlayer = qLevelMgr::GetInst()->FindObjectByName(L"Player");
	//
	//m_FSM->SetBlackboardData(L"Target", DATA_TYPE::OBJECT, pPlayer);
	//
	//m_FSM->ChangeState(L"Idle");
}

void qMonster_blue::tick()
{
}

void qMonster_blue::render()
{
	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();


	//// ��������
	//static float alpha = 0;
	//static float dir = 1;
	//
	//alpha += DT * 400.f * dir;
	//
	//if (255.f <= alpha)
	//{
	//	dir *= -1.f;
	//}
	//else if (alpha <= 0.f)
	//{
	//	dir *= -1.f;
	//}

	// AlphaBlending
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(DC
				, (int)(vPos.x - m_Img->GetWidth() * 0.5f)
				, (int)(vPos.y - m_Img->GetHeight() * 0.5f)
				, m_Img->GetWidth()
				, m_Img->GetHeight()
				, m_Img->GetDC()
				, 0, 0
				, m_Img->GetWidth(), m_Img->GetHeight()
				, bf);
}

void qMonster_blue::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	//if (_OtherObj->GetName() == L"Missile")
	//{
	//	--m_HP;
	//
	//	if (0 >= m_HP)
	//	{
	//		Destroy();
	//	}
	//}
}


