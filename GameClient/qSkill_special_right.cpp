#include "pch.h"
#include "qSkill_special_right.h"

#include "qCollider.h"
#include "qAnimator.h"
#include "qCamera.h"
#include "qSound.h"

#include "qTaskMgr.h"


qSkill_special_right::qSkill_special_right()
	: m_Animator(nullptr)
	, m_Collider(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation 추가
	qTexture* SpecialRight = qAssetMgr::GetInst()->LoadTexture(L"SpecialRight", L"texture\\skill\\special\\special_right.png");

	// 애니메이션 CREATE
	m_Animator->CreateAnimation(L"SpecialRight", SpecialRight, Vec2(0.f, 0.f), Vec2(580.f, 450.f), 11, 13);

	// 애니메이션 SAVE
	m_Animator->FindAnimation(L"SpecialRight")->Save(L"animation\\skill\\special\\");

	// 애니메이션 LOAD
	m_Animator->LoadAnimation(L"animation\\skill\\special\\SpecialRight.anim");

	m_Animator->Play(L"SpecialRight", false);


	// 콜라이더

	m_Collider = (qCollider*)AddComponent(new qCollider);

	m_Collider->SetOffsetPos(Vec2(80.f, 30.f));
	m_Collider->SetScale(Vec2(300.f, 300.f));



	// 스킬 사운드
	pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\skill\\special.wav");
	pSound->SetVolume(30.f);
	pSound->Play();
}

qSkill_special_right::qSkill_special_right(const qSkill_special_right& _Other)
	: m_Animator(nullptr)
	, m_Collider(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qSkill_special_right::~qSkill_special_right()
{
}

void qSkill_special_right::tick()
{
	qObj::tick();

	if (L"SpecialRight" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();

			pSound->SetVolume(30.f);
			pSound->Stop();
		}
	}
}

void qSkill_special_right::OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
}
