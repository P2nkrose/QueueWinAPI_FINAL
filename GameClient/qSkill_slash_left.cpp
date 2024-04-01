#include "pch.h"
#include "qSkill_slash_left.h"

#include "qCollider.h"
#include "qAnimator.h"
#include "qCamera.h"
#include "qSound.h"

#include "qTaskMgr.h"

qSkill_slash_left::qSkill_slash_left()
	: m_Animator(nullptr)
	, m_Collider(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation 추가
	qTexture* SlashLeft = qAssetMgr::GetInst()->LoadTexture(L"SlashLeft", L"texture\\skill\\slash\\slash_left.png");

	// 애니메이션 CREATE
	m_Animator->CreateAnimation(L"SlashLeft", SlashLeft, Vec2(0.f, 0.f), Vec2(675.f, 215.f), 11, 13);

	// 애니메이션 SAVE
	m_Animator->FindAnimation(L"SlashLeft")->Save(L"animation\\skill\\slash\\");

	// 애니메이션 LOAD
	m_Animator->LoadAnimation(L"animation\\skill\\slash\\SlashLeft.anim");

	m_Animator->Play(L"SlashLeft", false);


	// 콜라이더

	m_Collider = (qCollider*)AddComponent(new qCollider);

	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetScale(Vec2(450.f, 130.f));


	// 스킬 사운드
	pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\skill\\slash.wav");
	pSound->SetVolume(30.f);
	pSound->Play();
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

	SetPos(m_Owner->GetPos());

	if (L"SlashLeft" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();

			pSound->SetVolume(30.f);
			pSound->Stop();
		}
	}
}

void qSkill_slash_left::OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{

}
