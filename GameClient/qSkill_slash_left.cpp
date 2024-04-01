#include "pch.h"
#include "qSkill_slash_left.h"

#include "qCollider.h"
#include "qAnimator.h"
#include "qCamera.h"

#include "qTaskMgr.h"

qSkill_slash_left::qSkill_slash_left()
	: m_Animator(nullptr)
	, m_Collider(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation 추가
	qTexture* SlashLeft = qAssetMgr::GetInst()->LoadTexture(L"SlashLeft", L"texture\\skill\\slash\\slash_left.png");

	// 애니메이션 CREATE
	m_Animator->CreateAnimation(L"SlashLeft", SlashLeft, Vec2(0.f, 0.f), Vec2(675.f, 215.f), 11, 5);

	// 애니메이션 SAVE
	m_Animator->FindAnimation(L"SlashLeft")->Save(L"animation\\skill\\slash\\");

	// 애니메이션 LOAD
	m_Animator->LoadAnimation(L"animation\\skill\\slash\\SlashLeft.anim");

	m_Animator->Play(L"SlashLeft", false);


	// 콜라이더

	m_Collider = (qCollider*)AddComponent(new qCollider);

	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetScale(Vec2(675.f, 215.f));
}

qSkill_slash_left::qSkill_slash_left(const qSkill_slash_left& _Other)
	: m_Animator(nullptr)
	, m_Collider(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qSkill_slash_left::~qSkill_slash_left()
{
}

void qSkill_slash_left::tick()
{
	qObj::tick();

	if (L"SlashLeft" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();
		}
	}
}

void qSkill_slash_left::OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{

}
