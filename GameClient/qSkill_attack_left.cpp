#include "pch.h"
#include "qSkill_attack_left.h"

#include "qCollider.h"
#include "qAnimator.h"
#include "qCamera.h"
#include "qSound.h"

#include "qTaskMgr.h"


qSkill_attack_left::qSkill_attack_left()
	: m_Animator(nullptr)
	, m_Collider(nullptr)
{
	// 애니메이션
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// 애니메이션 추가
	qTexture* AttackLeft = qAssetMgr::GetInst()->LoadTexture(L"AttackLeft", L"texture\\skill\\attack\\attack_left.png");

	// 애니메이션 CREATE
	m_Animator->CreateAnimation(L"AttackLeft", AttackLeft, Vec2(0.f, 0.f), Vec2(410.f, 240.f), 12, 13);

	// 애니메이션 SAVE
	m_Animator->FindAnimation(L"AttackLeft")->Save(L"animation\\skill\\attack\\");

	// 애니메이션 LOAD
	m_Animator->LoadAnimation(L"animation\\skill\\attack\\AttackLeft.anim");

	m_Animator->Play(L"AttackLeft", false);


	// 콜라이더

	m_Collider = (qCollider*)AddComponent(new qCollider);

	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetScale(Vec2(350.f, 200.f));


	// 스킬 사운드
	pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\skill\\attack.wav");
	pSound->SetVolume(30.f);
	pSound->Play();

}

qSkill_attack_left::qSkill_attack_left(const qSkill_attack_left& _Other)
	: m_Animator(nullptr)
	, m_Collider(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qSkill_attack_left::~qSkill_attack_left()
{
}

void qSkill_attack_left::tick()
{
	qObj::tick();

	if (L"AttackLeft" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();

			pSound->SetVolume(30.f);
			pSound->Stop();
		}
	}
}

void qSkill_attack_left::OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
}
