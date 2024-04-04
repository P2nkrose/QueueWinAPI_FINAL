#include "pch.h"
#include "qSkill_slash_left.h"

#include "qCollider.h"
#include "qAnimator.h"
#include "qCamera.h"
#include "qSound.h"

#include "qLevel.h"
#include "qLevelMgr.h"

#include "qEffect_slash.h"
#include "qDamage_slash.h"

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

	m_Collider->SetOffsetPos(Vec2(-100.f, 0.f));
	m_Collider->SetScale(Vec2(250.f, 100.f));


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

void qSkill_slash_left::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	if (LAYER_TYPE::MONSTER_BLUE == _OtherObj->GetLayerType() || LAYER_TYPE::BOSS == _OtherObj->GetLayerType()
		|| LAYER_TYPE::MONSTER_RED == _OtherObj->GetLayerType())
	{
		qEffect_slash* pSlashEffect = new qEffect_slash;
		pSlashEffect->SetName(L"SlashEffect");

		Vec2 vSlashEffectPos = _OtherObj->GetPos() + Vec2(30.f, 0.f);
		Vec2 vSlashEffectScale = Vec2(200.f, 200.f);

		pSlashEffect->SetPos(vSlashEffectPos);
		pSlashEffect->SetScale(vSlashEffectScale);

		if (L"SlashEffect" == pSlashEffect->GetName())
		{
			// TASK
			SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::EFFECT, pSlashEffect);
		}
	}

	if (LAYER_TYPE::MONSTER_BLUE == _OtherObj->GetLayerType() || LAYER_TYPE::BOSS == _OtherObj->GetLayerType()
		|| LAYER_TYPE::MONSTER_RED == _OtherObj->GetLayerType())
	{
		qDamage_slash* pDamageSlash = new qDamage_slash;
		pDamageSlash->SetName(L"DamageSlash");

		Vec2 vDamageSlashPos = _OtherObj->GetPos() + Vec2(0.f, -90.f);
		Vec2 vDamageSlashScale = Vec2(258.f, 112.f);

		pDamageSlash->SetPos(vDamageSlashPos);
		pDamageSlash->SetScale(vDamageSlashScale);

		if (L"DamageSlash" == pDamageSlash->GetName())
		{
			// TASK
			SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::EFFECT, pDamageSlash);
		}
	}
}

