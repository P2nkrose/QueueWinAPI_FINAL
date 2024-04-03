#include "pch.h"
#include "qSkill_slash_right.h"

#include "qCollider.h"
#include "qAnimator.h"
#include "qCamera.h"
#include "qSound.h"

#include "qLevel.h"
#include "qLevelMgr.h"

#include "qEffect_slash.h"

#include "qTaskMgr.h"

qSkill_slash_right::qSkill_slash_right()
	: m_Animator(nullptr)
	, m_Collider(nullptr)
	, m_Owner(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation �߰�
	qTexture* SlashRight = qAssetMgr::GetInst()->LoadTexture(L"SlashRight", L"texture\\skill\\slash\\slash_right.png");

	// �ִϸ��̼� CREATE
	m_Animator->CreateAnimation(L"SlashRight", SlashRight, Vec2(0.f, 0.f), Vec2(675.f, 215.f), 11, 13);

	// �ִϸ��̼� SAVE
	m_Animator->FindAnimation(L"SlashRight")->Save(L"animation\\skill\\slash\\");

	// �ִϸ��̼� LOAD
	m_Animator->LoadAnimation(L"animation\\skill\\slash\\SlashRight.anim");

	m_Animator->Play(L"SlashRight", false);


	// �ݶ��̴�

	m_Collider = (qCollider*)AddComponent(new qCollider);

	m_Collider->SetOffsetPos(Vec2(100.f, 0.f));
	m_Collider->SetScale(Vec2(250.f, 100.f));


	// ��ų ����
	pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\skill\\slash.wav");
	pSound->SetVolume(30.f);
	pSound->Play();
}

qSkill_slash_right::qSkill_slash_right(const qSkill_slash_right& _Other)
	: m_Animator(nullptr)
	, m_Collider(nullptr)
	, m_Owner(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qSkill_slash_right::~qSkill_slash_right()
{
}

void qSkill_slash_right::tick()
{
	qObj::tick();


	SetPos(m_Owner->GetPos());

	if (L"SlashRight" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();

			pSound->SetVolume(30.f);
			pSound->Stop();
		}
	}
}

void qSkill_slash_right::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	if (LAYER_TYPE::MONSTER_BLUE == _OtherObj->GetLayerType() || LAYER_TYPE::BOSS == _OtherObj->GetLayerType()
		|| LAYER_TYPE::MONSTER_RED == _OtherObj->GetLayerType())
	{
		qEffect_slash* pSlashEffect = new qEffect_slash;
		pSlashEffect->SetName(L"SlashEffect");

		Vec2 vSlashEffectPos = _OtherObj->GetPos() + Vec2(-30.f, 0.f);
		Vec2 vSlashEffectScale = Vec2(200.f, 200.f);

		pSlashEffect->SetPos(vSlashEffectPos);
		pSlashEffect->SetScale(vSlashEffectScale);

		if (L"SlashEffect" == pSlashEffect->GetName())
		{
			// TASK
			SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::EFFECT, pSlashEffect);
		}
	}
}

