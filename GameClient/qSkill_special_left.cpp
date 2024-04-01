#include "pch.h"
#include "qSkill_special_left.h"

#include "qCollider.h"
#include "qAnimator.h"
#include "qCamera.h"

#include "qTaskMgr.h"


qSkill_special_left::qSkill_special_left()
	: m_Animator(nullptr)
	, m_Collider(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation 추가
	qTexture* SpecialLeft = qAssetMgr::GetInst()->LoadTexture(L"SpecialLeft", L"texture\\skill\\special\\special_left.png");

	// 애니메이션 CREATE
	m_Animator->CreateAnimation(L"SpecialLeft", SpecialLeft, Vec2(0.f, 0.f), Vec2(580.f, 450.f), 11, 13);

	// 애니메이션 SAVE
	m_Animator->FindAnimation(L"SpecialLeft")->Save(L"animation\\skill\\special\\");

	// 애니메이션 LOAD
	m_Animator->LoadAnimation(L"animation\\skill\\special\\SpecialLeft.anim");

	m_Animator->Play(L"SpecialLeft", false);


	// 콜라이더

	m_Collider = (qCollider*)AddComponent(new qCollider);

	m_Collider->SetOffsetPos(Vec2(-80.f, 30.f));
	m_Collider->SetScale(Vec2(300.f, 300.f));
}

qSkill_special_left::qSkill_special_left(const qSkill_special_left& _Other)
	: m_Animator(nullptr)
	, m_Collider(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qSkill_special_left::~qSkill_special_left()
{
}

void qSkill_special_left::tick()
{
	qObj::tick();

	if (L"SpecialLeft" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();
		}
	}
}

void qSkill_special_left::OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
}
